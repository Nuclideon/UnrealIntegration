#include "UDSubsystem.h"
#include "Runtime/RHI/Public/RHI.h"
#include "ImageUtils.h"
#include "Slate/SceneViewport.h"
#include "Engine/GameViewportClient.h"
#include "UDSettings.h"
#include "UDSceneViewExtension.h"
#include "UDDefine.h"
#include "udContext.h"
#include "Misc/MessageDialog.h"
#include "RenderingThread.h"

uint32_t vcVoxelShader_Black(udPointCloud* /*pPointCloud*/, const udVoxelID* /*pVoxelID*/, const void* pUserData)
{
	return 0x00000000;
}

uint32_t vcVoxelShader_Colour(udPointCloud* pPointCloud, const udVoxelID* pVoxelID, const void* pUserData)
{
	uint32_t color = 0;
	udPointCloud_GetNodeColour(pPointCloud, pVoxelID, &color);

	return (0xffffff & color);
}

void FuncMat2Array(double* array, const FMatrix& Mat)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			array[i * 4 + j] = Mat.M[i][j];
};

UUDSubsystem::UUDSubsystem()
{
	NextID = 1;

	Width = 0;
	Height = 0;
	ViewExtension = nullptr;
}

UUDSubsystem::~UUDSubsystem()
{
	if (HasSession())
		Exit();
}

void UUDSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | INIT SUBSYSTEM"));

	// Register the view extension immediately and unconditionally so
	// BeginRenderViewFamily is always called regardless of session state.
	// The extension checks HasSession() internally before doing any work.
	ViewExtension = FSceneViewExtensions::NewExtension<FUDSceneViewExtension>();

	LoginFunction();
}

void UUDSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | DEINIT SUBSYSTEM"));
	Exit();
	// Release the extension only on full subsystem teardown, not on logout,
	// so it stays registered through connect/disconnect cycles.
	ViewExtension = nullptr;
}

// Does NOT init the udContext
int UUDSubsystem::Init()
{
	enum udError error = udE_Success;

	if (const UUDSettings* Settings = GetDefault<UUDSettings>())
	{
		ServerUrl = Settings->ServerPath;
		APIKey = Settings->APIKey;
		if (ServerUrl.IsEmpty() || APIKey.IsEmpty())
			error = udE_Failure;
	}
	else
	{
		ServerUrl = "udcloud.com";
		APIKey = "";
		error = udE_Failure;
	}

	return error;
}

// Called as a result of clicking Login() from the widget
int UUDSubsystem::LoginFunction()
{
	// Logging startup values at login
	UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Connecting to Server: '%s'"), *ServerUrl);

	// Get an error ready and default to failure
	enum udError error = udE_Failure;

	// Unsure what happens to login reqs
	if (HasSession())
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Have login!"));
		return error;
	}

	// Initialize login related data
	// Will fail if logins are not entered into the UI etc
	error = (udError)Init(); // Maybe fix this cast?
	
	if (error != udE_Success) // Should fail basically due to user error only
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | Initialization failed!"));
		return error;
	}
	
	{
		FScopeLock ScopeLockInst(&DataMutex);
		RenderInstanceHandles.Reset();
		AssetsMap.Reset();
	}

	if (ServerUrl.IsEmpty() || APIKey.IsEmpty())
	{
		FMessageDialog::Debugf(FText::FromString("Unlimited Detail settings are invalid please ensure server and APIKey are correct in the project settings and restart the application."));
		return udE_Failure;
	}

	const FString ApplicationVersion = "0.0";
	const FString ApplicationName = "UE5_Client";

	error = udContext_ConnectWithKey(&pContext, TCHAR_TO_UTF8(*ServerUrl), TCHAR_TO_UTF8(*ApplicationName), TCHAR_TO_UTF8(*ApplicationVersion), TCHAR_TO_UTF8(*APIKey));
	if (error != udE_Success)
	{
		FString message = FString::Printf(TEXT("udContext_ConnectWithKey (Error: %s)"), *GetError(error));
		FMessageDialog::Debugf(FText::FromString(message));
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udContext_ConnectWithKey (Error: %s)"), *GetError(error));
		return error;
	}

	error = udRenderContext_Create(pContext, &pRenderer);
	if (error != udE_Success)
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udRenderContext_Create (Error: %s)"), *GetError(error));
		return error;
	}

	return error;
}

void UUDSubsystem::Exit()
{
	// ViewExtension is intentionally NOT cleared here — it must survive logout/reconnect
	// cycles and is only released in Deinitialize().

	ServerUrl = ""; // udcloud.com
	APIKey = "";

	Width = 0;
	Height = 0;

	FScopeLock ScopeLock(&DataMutex);
	for (auto inst : AssetsMap)
	{
		udPointCloud_Unload(&inst.Value.PointCloud);
	}

	RenderInstanceHandles.Reset();
	AssetsMap.Reset();

	udRenderTarget_Destroy(&pRenderView);
	udRenderContext_Destroy(&pRenderer);
	udContext_Disconnect(&pContext, false);
}

FUDPointCloudHandle* UUDSubsystem::Load(FString URL)
{
	enum udError error = udE_Failure;

	if (!HasSession()) // Check again
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | Not logged in!"));
		return nullptr;
	}

	{
		FScopeLock ScopeLock(&DataMutex);
		FUDPointCloudHandle* AssetPtr = AssetsMap.Find(URL);
		if (AssetPtr)
		{
			++AssetPtr->RefCount;
			UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Fetched [In Cache: %d] | %s"), AssetPtr->RefCount, *AssetPtr->URL);
			return AssetPtr;
		}
	}

	FUDPointCloudHandle Asset = {};
	udPointCloudHeader header = {};

	Asset.URL = URL;

	error = udPointCloud_Load(pContext, &Asset.PointCloud, TCHAR_TO_UTF8(*URL), &header);
	if (error != udE_Success)
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udPointCloud_Load error : %s %s"), *GetError(error), *URL);
		return nullptr;
	}

	Asset.VoxelShaderFunc = vcVoxelShader_Black;

	uint32_t attributeOffset = 0;
	if (udAttributeSet_GetOffsetOfStandardAttribute(&header.attributes, udSA_ARGB, &attributeOffset) == udE_Success)
	{
		Asset.VoxelShaderFunc = vcVoxelShader_Colour;
	}

	Asset.Pivot.X = header.pivot[0];
	Asset.Pivot.Y = header.pivot[1];
	Asset.Pivot.Z = header.pivot[2];

	Asset.bIsLoaded = true;
	Asset.RefCount = 1;

	{
		FScopeLock ScopeLock(&DataMutex);

		// Double check it doesn't already exist again
		FUDPointCloudHandle *AssetPtr = AssetsMap.Find(URL);
		if (AssetPtr)
		{
			++AssetPtr->RefCount;

			udPointCloud_Unload(&Asset.PointCloud);

			UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Fetched [Cache Missed: %d] | %s"), AssetPtr->RefCount, *AssetPtr->URL);

			return AssetPtr;
		}
		else
		{
			AssetsMap.Add(URL, Asset);

			UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Fetched [Added to cache: %d] | %s"), Asset.RefCount, *Asset.URL);
			return AssetsMap.Find(URL);
		}
	}
}

void UUDSubsystem::Remove(FUDPointCloudHandle* PCI)
{
	FScopeLock ScopeLock(&DataMutex);

	if (PCI == nullptr || PCI->RefCount <= 0)
		return;

	FUDPointCloudHandle* Asset = AssetsMap.Find(PCI->URL);

	if (Asset == PCI)
	{
		--Asset->RefCount;

		UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Releasing [Cached:%d] | %s"), Asset->RefCount, *Asset->URL);

		if (Asset->RefCount == 0)
		{
			for (int i = RenderInstanceHandles.Num() - 1; i >= 0; --i)
			{
				if (RenderInstanceHandles[i].RenderInstance.pPointCloud == PCI->PointCloud)
				{
					RenderInstanceHandles.RemoveAtSwap(i);
				}
			}

			FString key = PCI->URL;
			udPointCloud_Unload(&PCI->PointCloud);
			AssetsMap.Remove(key);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Remove: handle %p does not match cached entry for URL '%s'"), PCI, *PCI->URL);
	}
}

bool UUDSubsystem::Find(FString URL)
{
	FScopeLock ScopeLock(&DataMutex);
	FUDPointCloudHandle* Asset = AssetsMap.Find(URL);

	return (Asset != nullptr);
}


int64_t UUDSubsystem::QueueInstance(FUDPointCloudHandle *PCI, const FMatrix &InMatrix, FSceneInterface *Scene)
{
	if (!PCI || !PCI->bIsLoaded || !PCI->PointCloud)
	{
		return -1;
	}

	FScopeLock ScopeLock(&DataMutex);

	FUDPointCloudInstanceHandle RenderInstance = {};
	RenderInstance.id = (NextID++);
	RenderInstance.Scene = Scene;

	RenderInstance.RenderInstance.pPointCloud = PCI->PointCloud;
	RenderInstance.RenderInstance.pVoxelShader = PCI->VoxelShaderFunc;

	for (int i = 0; i < 4; ++i)
	{
		RenderInstance.RenderInstance.matrix[0 + i * 4] = InMatrix.M[i][0];
		RenderInstance.RenderInstance.matrix[1 + i * 4] = InMatrix.M[i][1];
		RenderInstance.RenderInstance.matrix[2 + i * 4] = InMatrix.M[i][2];
		RenderInstance.RenderInstance.matrix[3 + i * 4] = InMatrix.M[i][3];
	}

	RenderInstanceHandles.Push(RenderInstance);

	return RenderInstance.id;
}

bool UUDSubsystem::RemoveInstance(int64_t id)
{
	FScopeLock ScopeLock(&DataMutex);
	for (int i = 0; i < RenderInstanceHandles.Num(); ++i)
	{
		if (RenderInstanceHandles[i].id != id)
			continue;

		RenderInstanceHandles.RemoveAt(i);
		return true;
	}

	return false;
}

bool UUDSubsystem::UpdateInstance(int64_t id, const FMatrix &InMatrix)
{
	FScopeLock ScopeLock(&DataMutex);

	//TODO: Binary search this instead
	for (int i = 0; i < RenderInstanceHandles.Num(); ++i)
	{
		if (RenderInstanceHandles[i].id != id)
			continue;

		for (int j = 0; j < 4; ++j)
		{
			RenderInstanceHandles[i].RenderInstance.matrix[0 + j * 4] = InMatrix.M[j][0];
			RenderInstanceHandles[i].RenderInstance.matrix[1 + j * 4] = InMatrix.M[j][1];
			RenderInstanceHandles[i].RenderInstance.matrix[2 + j * 4] = InMatrix.M[j][2];
			RenderInstanceHandles[i].RenderInstance.matrix[3 + j * 4] = InMatrix.M[j][3];
		}

		return true;
	}

	return false;
}

// The main function for rendering out UD images
int UUDSubsystem::CaptureUDSImage(const FSceneView& View)
{
	// prep an empty error
	enum udError error = udE_Failure;
	
	if (!HasSession())
	{
		return udE_Failure;
	}

	{
		FScopeLock ScopeLock(&DataMutex);
		if (RenderInstanceHandles.Num() == 0)
		{
			return udE_Failure;
		}
	}

	// These values are incorrect, but are at least visually plausable.
	// If we can however get our singleton correctly, we should use the more accurate values contained within that
	// auto vartest = View.UnconstrainedViewRect.Width();
	int32 nWidth = View.UnconstrainedViewRect.Width();
	int32 nHeight = View.UnconstrainedViewRect.Height();
	
	// Return early if we have really invalid values?
	if (nWidth <= 0 || nHeight <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | Error, width or height = 0 : %s"), *GetError(error));
		return udE_Failure;
	}

	// Hardcap: excessively large dimensions usually mean this frame should not render
	if (nWidth >= 8192 || nHeight >= 8192)
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | Error, width (%d) or height (%d) exceeds 8192 limit"), nWidth, nHeight);
		return udE_Failure;
	}

	error = (udError)RecreateUDView(nWidth, nHeight, View.FOV);
	if (error != udE_Success)
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | RecreateUDView error : %s"), *GetError(error));
		return error;
	}

	FuncMat2Array(ProjArray, ProjectionMatrix);
	FuncMat2Array(ViewArray, View.ViewMatrices.GetViewMatrix());

	{
		FScopeLock ScopeLockInst(&DataMutex);

		error = udRenderTarget_SetTargets(pRenderView, ColorBulkData.GetData(), 0xFF000000, DepthBulkData.GetData());
		if (error != udE_Success)
		{
			UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udRenderTarget_SetTargets error : %s"), *GetError(error));
			return error;
		}

		error = udRenderTarget_SetMatrix(pRenderView, udRTM_Projection, ProjArray);
		if (error != udE_Success)
		{
			UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udRenderTarget_SetMatrix (Projection) error : %s"), *GetError(error));
			return error;
		}

		error = udRenderTarget_SetMatrix(pRenderView, udRTM_View, ViewArray);
		if (error != udE_Success)
		{
			UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udRenderTarget_SetMatrix (View) error : %s"), *GetError(error));
			return error;
		}

		udRenderPicking picking = {};

		udRenderSettings renderOptions;
		memset(&renderOptions, 0, sizeof(udRenderSettings));
		
		renderOptions.pPick = &picking;
		renderOptions.pFilter = nullptr;
		renderOptions.pointMode = udRCPM_Rectangles;
		
		TArray<udRenderInstance> RenderInstances;

		for (int i = 0; i < RenderInstanceHandles.Num(); ++i)
		{
			if (RenderInstanceHandles[i].Scene == View.Family->Scene)
			{
				RenderInstances.Add(RenderInstanceHandles[i].RenderInstance);
			}
		}

		error = udRenderContext_Render(pRenderer, pRenderView, RenderInstances.GetData(), RenderInstances.Num(), &renderOptions);
		if (error != udE_Success)
		{
			UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udRenderContext_Render error : %s"), *GetError(error));
			return error;
		}

		// TODO - Add picking back in
		if (picking.hit)
		{
		//	SetSelectedByModelIndex(picking.modelIndex, true);
		}
	}


	// Upload CPU buffers to the CPUWritable textures via lock/unlock.
	// This writes directly into upload-heap memory — no GPU DMA copy is required.
	// Row stride from RHILockTexture2D may exceed Width*bpp (D3D12 requires 256-byte
	// row alignment), so we copy row-by-row when the strides differ.
	ENQUEUE_RENDER_COMMAND(UpdateTextureData)(
		[this](FRHICommandListImmediate& RHICmdList)
		{
			FScopeLock ScopeLock(&DataMutex);

			auto UploadToTexture = [](FRHITexture* Texture, const void* SrcData, uint32 SrcRowBytes, int32 InHeight)
			{
				uint32 DestStride = 0;
				void* Dest = RHILockTexture2D(Texture, 0, RLM_WriteOnly, DestStride, false);
				if (!Dest)
					return;

				if (DestStride == SrcRowBytes)
				{
					FMemory::Memcpy(Dest, SrcData, (SIZE_T)SrcRowBytes * InHeight);
				}
				else
				{
					for (int32 Row = 0; Row < InHeight; ++Row)
					{
						FMemory::Memcpy(
							static_cast<uint8*>(Dest)       + (SIZE_T)Row * DestStride,
							static_cast<const uint8*>(SrcData) + (SIZE_T)Row * SrcRowBytes,
							SrcRowBytes
						);
					}
				}

				RHIUnlockTexture2D(Texture, 0, false);
			};

			if (ColorTexture.IsValid() && ColorTexture->GetSizeX() == Width && ColorTexture->GetSizeY() == Height)
				UploadToTexture(ColorTexture.GetReference(), ColorBulkData.GetData(), Width * ColorBulkData.GetTypeSize(), Height);

			if (DepthTexture.IsValid() && DepthTexture->GetSizeX() == Width && DepthTexture->GetSizeY() == Height)
				UploadToTexture(DepthTexture.GetReference(), DepthBulkData.GetData(), Width * DepthBulkData.GetTypeSize(), Height);
		}
	);
	return error;
}

int UUDSubsystem::RecreateUDView(int32 InWidth, int32 InHeight, float InFOV)
{
	enum udError error = udE_Success;
	if (InWidth == Width && InHeight == Height)
	{
		return error;
	}

	Width = InWidth;
	Height = InHeight;

	UE_LOG(LogTemp, Display, TEXT("RecreateUDView() Width: %d, Height: %d"), Width, Height);
			

	const float MinZ = GNearClippingPlane;
	const float MaxZ = MinZ;
	const float ModifiedViewFOV = InFOV;
	const float MatrixFOV = FMath::Max(0.001f, ModifiedViewFOV) * (float)PI / 360.0f;

	float const XAxisMultiplier = 1.0f;
	float const YAxisMultiplier = Width / (float)Height;

	ProjectionMatrix = FPerspectiveMatrix(
		MatrixFOV,
		MatrixFOV,
		XAxisMultiplier,
		YAxisMultiplier,
		MinZ,
		MaxZ
	);

	{
		FScopeLock ScopeLock(&DataMutex);
		ColorBulkData.ResizeArray(Width * Height);
		DepthBulkData.ResizeArray(Width * Height);
	}

	// RHICreateTexture must be called from the render thread. Resize is infrequent
	// so flushing here to ensure the textures are ready before the first upload is fine.
	ENQUEUE_RENDER_COMMAND(RecreateUDTextures)([this, NewWidth = Width, NewHeight = Height](FRHICommandListImmediate&)
	{
		// TexCreate_CPUWritable is D3D12-only (upload heap). On D3D11 it strips
		// D3D11_BIND_SHADER_RESOURCE, preventing SRV creation and crashing at bind time.
		// TexCreate_Dynamic is correct for both APIs: CPU-writable, GPU-readable, SRV-capable.
		const ETextureCreateFlags TexCreateFlags = TexCreate_Dynamic;

		FScopeLock ScopeLock(&DataMutex);

		FRHITextureCreateDesc ColorDesc = FRHITextureCreateDesc::Create2D(TEXT("UDColorTexture"), NewWidth, NewHeight, EPixelFormat::PF_B8G8R8A8);
		ColorDesc.SetFlags(TexCreateFlags).SetNumMips(1).SetNumSamples(1);
		ColorTexture = RHICreateTexture(ColorDesc);

		FRHITextureCreateDesc DepthDesc = FRHITextureCreateDesc::Create2D(TEXT("UDDepthTexture"), NewWidth, NewHeight, EPixelFormat::PF_R32_FLOAT);
		DepthDesc.SetFlags(TexCreateFlags).SetNumMips(1).SetNumSamples(1);
		DepthTexture = RHICreateTexture(DepthDesc);
	});
	// FlushRenderingCommands() must only be called from the game thread.
	// BeginRenderViewFamily runs on the render thread in UE5.7, so guard accordingly.
	if (IsInGameThread())
	{
		FlushRenderingCommands();
	}

	

	if (pRenderView)
	{
		error = udRenderTarget_Destroy(&pRenderView);
		if (error != udE_Success)
		{
			UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udRenderTarget_Destroy error : %s"), *GetError(error));
			return error;
		}
		pRenderView = nullptr;
	}

	
	error = udRenderTarget_Create(pContext, &pRenderView, pRenderer, Width, Height);
	
	if (error != udE_Success)
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | udRenderTarget_Create error : %s"), *GetError(error));
	}

	return error;
}

