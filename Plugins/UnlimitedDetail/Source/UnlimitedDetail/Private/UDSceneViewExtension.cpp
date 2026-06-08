#include "UDSceneViewExtension.h"
#include "UDSubsystem.h"
#include "GlobalShader.h"
#include "SceneView.h"
#include "PixelShaderUtils.h"
#include "RHIStaticStates.h"

#include "UDComposite.h"
#include "PostProcess/SceneRenderTargets.h"
#include "Runtime/Renderer/Private/SceneRendering.h"
#include "PostProcess/PostProcessInputs.h"

// =====================================================================================
//
// DEPTH INJECT SHADER
// Writes UD geometry depth into the hardware depth buffer (reversed-Z) so that
// transparent objects rendered in the translucency pass correctly sort against UD.
//
// =====================================================================================

class FUdsDepthInjectPS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FUdsDepthInjectPS);
	SHADER_USE_PARAMETER_STRUCT(FUdsDepthInjectPS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_TEXTURE(Texture2D, UdDepthTexture)
		SHADER_PARAMETER(FVector2f, ViewRectMin)
		SHADER_PARAMETER(float, ColorDepthRatioX)
		SHADER_PARAMETER(float, ColorDepthRatioY)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
};

IMPLEMENT_GLOBAL_SHADER(FUdsDepthInjectPS, "/Plugins/UnlimitedDetail/Private/Uds_DepthInject.usf", "MainPS", SF_Pixel);

// =====================================================================================
//
// COLOR INJECT SHADER
// Composites UD geometry colour into scene colour *before* the post-process chain
// (PrePostProcessPass_RenderThread), so that AfterDOF / AfterMotionBlur translucent
// objects subsequently composite on top of UD correctly.
//
// Uses ERenderTargetLoadAction::ELoad + discard so that non-UD pixels keep their
// existing scene colour — no extra copy texture required.
//
// =====================================================================================

class FUdsColorInjectPS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FUdsColorInjectPS);
	SHADER_USE_PARAMETER_STRUCT(FUdsColorInjectPS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_TEXTURE(Texture2D, UdColorTexture)
		SHADER_PARAMETER_TEXTURE(Texture2D, UdDepthTexture)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D<float>, SceneDepth)
		SHADER_PARAMETER(FVector2f, ViewRectMin)
		SHADER_PARAMETER(float, ColorDepthRatioX)
		SHADER_PARAMETER(float, ColorDepthRatioY)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
};

IMPLEMENT_GLOBAL_SHADER(FUdsColorInjectPS, "/Plugins/UnlimitedDetail/Private/Uds_ColorInject.usf", "MainPS", SF_Pixel);

// -------------------------------------------------------------------------------------

FUDSceneViewExtension::FUDSceneViewExtension(const FAutoRegister& AutoRegister) :
	FSceneViewExtensionBase(AutoRegister)
{

}


void FUDSceneViewExtension::SetupViewFamily(FSceneViewFamily &InViewFamily)
{
	// Required to be implemented by abstract parent class
}

void FUDSceneViewExtension::SetupView(FSceneViewFamily &InViewFamily, FSceneView &InView)
{
	// Required to be implemented by abstract parent class
}


void FUDSceneViewExtension::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	// TODO - It would be ideal if this function could correctly marshal the true depth buffer width/height down into the CaptureUDSImage call below
	// I'm unsure of how to do that right now, so for now these values are being cached into a UDSDK engine singleton
	// but this really should be refactored at a later date.

	UUDSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UUDSubsystem>();

	if (!MySubsystem ||	InViewFamily.Views.Num() == 0)
	{
		return;
	}

	if (InViewFamily.GetFeatureLevel() >= ERHIFeatureLevel::SM5)
	{
		for (int i = 0; i < InViewFamily.Views.Num(); i++)
		{
			const FSceneView* InView = InViewFamily.Views[i];

			if (ensure(InView))
			{
				MySubsystem->CaptureUDSImage(*InView);
			}
		}

		// Push UD colour and depth textures to the render thread so that
		// PostRenderBasePassDeferred and PrePostProcessPass can use them.
		// BeginRenderViewFamily always runs before this frame's render work begins, so
		// both enqueued commands are guaranteed to execute before those hooks fire.
		FTextureRHIRef CapturedColorTex = MySubsystem->GetColorTexture();
		FTextureRHIRef CapturedDepthTex = MySubsystem->GetDepthTexture();

		ENQUEUE_RENDER_COMMAND(CacheUDTexturesForInject)(
			[this, CapturedColorTex, CapturedDepthTex](FRHICommandListImmediate&)
			{
				RT_UdColorTexture = CapturedColorTex;
				RT_UdDepthTexture = CapturedDepthTex;
			}
		);

		// NOTE: We deliberately do NOT call SetSecondarySpatialUpscalerInterface here.
		// UD colour compositing is now handled in PrePostProcessPass_RenderThread (before
		// the post-process chain), which lets AfterDOF / AfterMotionBlur translucent
		// objects correctly composite on top of UD.  The old ISpatialUpscaler compositor
		// (FUDComposite) would run after all translucency had already been flattened into
		// scene colour, making it impossible for any transparent object to appear in front
		// of UD geometry.
	}
}

void FUDSceneViewExtension::PostRenderBasePassDeferred_RenderThread(
	FRDGBuilder& GraphBuilder, FSceneView& InView,
	const FRenderTargetBindingSlots& /*RenderTargets*/,
	TRDGUniformBufferRef<FSceneTextureUniformParameters> /*SceneTexturesUniformBuffer*/)
{
	if (!RT_UdDepthTexture.IsValid())
		return;

	// The renderer always passes FViewInfo instances; the base interface exposes FSceneView.
	FViewInfo& View = static_cast<FViewInfo&>(InView);

	const FSceneTextures* SceneTextures = View.GetSceneTexturesChecked();
	if (!SceneTextures)
		return;

	FUdsDepthInjectPS::FParameters* PassParameters =
		GraphBuilder.AllocParameters<FUdsDepthInjectPS::FParameters>();

	// Compute the ratio from depth-buffer pixel space → UD texture pixel space.
	// The UD texture is captured at UnconstrainedViewRect resolution (same as colour output);
	// the depth buffer is at ViewRect resolution (smaller under TSR/TAA/render scaling).
	// This is the same mismatch the compositor fixes with ColorDepthExtentRatio.
	const FIntPoint DepthExtent  = SceneTextures->Depth.Target->Desc.Extent;
	const FIntPoint UdTexExtent  = FIntPoint(RT_UdDepthTexture->GetSizeX(), RT_UdDepthTexture->GetSizeY());

	PassParameters->UdDepthTexture   = RT_UdDepthTexture->GetTexture2D();
	PassParameters->ViewRectMin      = FVector2f(View.ViewRect.Min.X, View.ViewRect.Min.Y);
	PassParameters->ColorDepthRatioX = DepthExtent.X > 0 ? (float)UdTexExtent.X / DepthExtent.X : 1.0f;
	PassParameters->ColorDepthRatioY = DepthExtent.Y > 0 ? (float)UdTexExtent.Y / DepthExtent.Y : 1.0f;

	PassParameters->RenderTargets.DepthStencil = FDepthStencilBinding(
		SceneTextures->Depth.Target,
		ERenderTargetLoadAction::ELoad,
		ERenderTargetLoadAction::ENoAction,
		FExclusiveDepthStencil::DepthWrite_StencilNop);

	TShaderMapRef<FUdsDepthInjectPS> PixelShader(View.ShaderMap);

	// CF_GreaterEqual in reversed-Z means "write if the new depth value is closer or equal".
	// Pixels where UD is behind opaque geometry are discarded by the hardware depth test;
	// pixels with no UD geometry are discarded in the shader (UdDepth >= 0.999).
	FPixelShaderUtils::AddFullscreenPass(
		GraphBuilder,
		View.ShaderMap,
		RDG_EVENT_NAME("UD_DepthInject"),
		PixelShader,
		PassParameters,
		View.ViewRect,
		nullptr,   // BlendState   – no colour output
		nullptr,   // RasterizerState – default
		TStaticDepthStencilState<true, CF_GreaterEqual>::GetRHI()
	);
}

void FUDSceneViewExtension::PrePostProcessPass_RenderThread(
	FRDGBuilder& GraphBuilder, const FSceneView& InView,
	const FPostProcessingInputs& /*Inputs*/)
{
	if (!RT_UdColorTexture.IsValid() || !RT_UdDepthTexture.IsValid())
		return;

	// Cast is safe: the renderer always passes FViewInfo instances; const_cast is safe
	// because the underlying object is never actually const-qualified by the renderer.
	FViewInfo& View = static_cast<FViewInfo&>(const_cast<FSceneView&>(InView));

	const FSceneTextures* SceneTextures = View.GetSceneTexturesChecked();
	if (!SceneTextures)
		return;

	FUdsColorInjectPS::FParameters* PassParameters =
		GraphBuilder.AllocParameters<FUdsColorInjectPS::FParameters>();

	// Same UD-texture → scene-colour coordinate ratio as the depth inject pass.
	// At PrePostProcessPass time, scene colour is at render resolution (ViewRect),
	// while UD textures are at display resolution (UnconstrainedViewRect).
	const FIntPoint SceneColorExtent = SceneTextures->Color.Target->Desc.Extent;
	const FIntPoint UdTexExtent      = FIntPoint(RT_UdColorTexture->GetSizeX(), RT_UdColorTexture->GetSizeY());

	PassParameters->UdColorTexture   = RT_UdColorTexture->GetTexture2D();
	PassParameters->UdDepthTexture   = RT_UdDepthTexture->GetTexture2D();
	PassParameters->SceneDepth       = SceneTextures->Depth.Target;
	PassParameters->ViewRectMin      = FVector2f(View.ViewRect.Min.X, View.ViewRect.Min.Y);
	PassParameters->ColorDepthRatioX = SceneColorExtent.X > 0 ? (float)UdTexExtent.X / SceneColorExtent.X : 1.0f;
	PassParameters->ColorDepthRatioY = SceneColorExtent.Y > 0 ? (float)UdTexExtent.Y / SceneColorExtent.Y : 1.0f;

	// Bind scene colour as a render target with ELoad so that pixels the shader
	// discards keep their existing scene colour (no extra copy texture needed).
	PassParameters->RenderTargets[0] = FRenderTargetBinding(
		SceneTextures->Color.Target,
		ERenderTargetLoadAction::ELoad);

	TShaderMapRef<FUdsColorInjectPS> PixelShader(View.ShaderMap);

	FPixelShaderUtils::AddFullscreenPass(
		GraphBuilder,
		View.ShaderMap,
		RDG_EVENT_NAME("UD_ColorInject"),
		PixelShader,
		PassParameters,
		View.ViewRect
	);
}
