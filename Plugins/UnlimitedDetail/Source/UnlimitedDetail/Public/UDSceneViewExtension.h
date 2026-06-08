#pragma once

#include "SceneViewExtension.h"
#include "RHI.h"

class FUDSceneViewExtension final : public FSceneViewExtensionBase
{
public:
	FUDSceneViewExtension(const FAutoRegister& AutoRegister);

	void SetupViewFamily(FSceneViewFamily &InViewFamily) override;
	void SetupView(FSceneViewFamily &InViewFamily, FSceneView &InView) override;

	void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;

	// Called after the deferred base pass; injects UD depth into the hardware depth buffer
	// so the translucency pass can correctly sort transparent objects against UD geometry.
	void PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures) override;

	// Called just before AddPostProcessingPasses (i.e. after deferred lighting but before
	// the post-process chain). We composite UD colour into scene colour here so that
	// AfterDOF / AfterMotionBlur translucent objects — which haven't been flattened into
	// scene colour yet — subsequently composite on top of UD correctly.
	void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView, const FPostProcessingInputs& Inputs) override;

private:
	// UD colour and depth textures cached on the render thread each frame (written via
	// render command from BeginRenderViewFamily before any base-pass work begins).
	FTextureRHIRef RT_UdColorTexture;
	FTextureRHIRef RT_UdDepthTexture;
};