#include "UDComponent.h"
#include "Engine/World.h"
#include "UDDefine.h"
#include "UDSubsystem.h"

/** Represents a UArrowComponent to the scene manager. */
class FPointCloudSceneProxy final : public FPrimitiveSceneProxy
{
public:
	SIZE_T GetTypeHash() const override
	{
		static size_t UniquePointer;
		return reinterpret_cast<size_t>(&UniquePointer);
	}

	FPointCloudSceneProxy(UUDComponent* Component) : FPrimitiveSceneProxy(Component)
	{
		myRoot = Component;
		bWillEverBeLit = false;
		instance = -1;
		bShouldNotifyOnWorldAddRemove = true;
	}

	virtual ~FPointCloudSceneProxy()
	{
		if (instance != -1)
		{
			if (UUDSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UUDSubsystem>())
			{
				MySubsystem->RemoveInstance(instance);
				instance = -1;
			}
		}
	}

	// FPrimitiveSceneProxy interface.

	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
	{
		QUICK_SCOPE_CYCLE_COUNTER(STAT_ArrowSceneProxy_DrawDynamicElements);

		if (instance == -1)
		{
			// This Log shouldn't be required but it's helping to track down an issue that happens occasionally
			UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Getting dynamic mesh elements without mounted instance."));
		}
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
	{
		FPrimitiveViewRelevance Result;
		Result.bDrawRelevance = IsShown(View);
		Result.bDynamicRelevance = true;

		Result.bShadowRelevance = false; //TODO: Consider shadows support
		Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
		Result.bVelocityRelevance = false;

		return Result;
	}

	// Returns the world matrix to send to the udSDK renderer.
	//
	// The UD SDK's storedMatrix converts from unit cube [0,1]³ to the model's
	// native coordinate space.  The header's pivot is also in unit cube space and
	// marks the model's natural reference / handle point.
	//
	// ResetScale() bakes the storedMatrix axis magnitudes into the UE component
	// scale, so GetLocalToWorld() already has the right size.  What it does NOT
	// account for is the pivot offset: with a raw GetLocalToWorld() the unit cube
	// origin (0,0,0) aligns with the component gizmo, but the visual pivot of the
	// geometry may be elsewhere in [0,1]³.
	//
	// Fix: pre-translate the unit cube by -pivot before applying LocalToWorld so
	// that pivot → (0,0,0) → component world position.
	FMatrix GetPivotCorrectedMatrix() const
	{
		FMatrix Result = GetLocalToWorld();
		const FUDPointCloudHandle* Handle = myRoot ? myRoot->PointCloudHandle : nullptr;
		if (Handle && Handle->bIsLoaded)
		{
			// Build a translation matrix for -pivot (unit cube space).
			// UE FMatrix is row-major with translation in the last row (M[3]).
			FMatrix PivotOffset = FMatrix::Identity;
			PivotOffset.M[3][0] = -Handle->Pivot.X;
			PivotOffset.M[3][1] = -Handle->Pivot.Y;
			PivotOffset.M[3][2] = -Handle->Pivot.Z;

			// In UE, (A * B) applies A first then B for row vectors, so:
			//   P_world = P_unitcube * PivotOffset * LocalToWorld
			//           = (P_unitcube - pivot) * LocalToWorld
			// → when P_unitcube == pivot, P_world == component world position. ✓
			Result = PivotOffset * Result;
		}
		return Result;
	}

	// In UE5.5+ OnLevelAddedToWorld_RenderThread / OnLevelRemovedFromWorld_RenderThread
	// are no longer virtual. The base implementations call SetForceHidden, which
	// triggers this virtual hook instead.
	virtual void OnForceHiddenChanged() override
	{
		UUDSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UUDSubsystem>();
		if (!MySubsystem)
			return;

		if (!IsForceHidden())
		{
			check(instance == -1);
			instance = MySubsystem->QueueInstance(myRoot->PointCloudHandle, GetPivotCorrectedMatrix(), &GetScene(), myRoot);
		}
		else
		{
			if (instance != -1)
			{
				MySubsystem->RemoveInstance(instance);
				instance = -1;
			}
		}
	}

	virtual void OnTransformChanged(FRHICommandListBase& RHICmdList) override
	{
		UUDSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UUDSubsystem>();
		if (!MySubsystem)
			return;

		if (instance == -1)
			instance = MySubsystem->QueueInstance(myRoot->PointCloudHandle, GetPivotCorrectedMatrix(), &GetScene(), myRoot);
		else
			MySubsystem->UpdateInstance(instance, GetPivotCorrectedMatrix());
	}

	virtual uint32 GetMemoryFootprint(void) const override
	{
		return sizeof(*this) + GetAllocatedSize();
	}

	uint32 GetAllocatedSize(void) const
	{
		return FPrimitiveSceneProxy::GetAllocatedSize();
	}

private:
	UUDComponent* myRoot = nullptr;
	int64_t instance; //TODO: Find we need multiple of these
};


UUDComponent::UUDComponent()
{
	// Intentionally blank
	PointCloudHandle = nullptr;
	Url = "";
}

void UUDComponent::SetUrl(FString InUrl)
{
	if (InUrl != this->Url)
	{
		Url = InUrl;
		UnloadPointCloud();
		LoadPointCloud();
	}
}

void UUDComponent::RefreshPointCloud()
{
	UnloadPointCloud();
	LoadPointCloud();
}

void UUDComponent::ResetScale()
{
	if (!PointCloudHandle || !PointCloudHandle->bIsLoaded)
		return;

	// storedMatrix is column-major: columns 0/1/2 are the X/Y/Z axes.
	// The magnitude of each axis column gives the scale for that axis.
	const double* M = PointCloudHandle->StoredMatrix;
	const float Sx = 100.0 * (float)FMath::Sqrt(M[0]*M[0] + M[1]*M[1] + M[2]*M[2]);
	const float Sy = 100.0 * (float)FMath::Sqrt(M[4]*M[4] + M[5]*M[5] + M[6]*M[6]);
	const float Sz = 100.0 * (float)FMath::Sqrt(M[8]*M[8] + M[9]*M[9] + M[10]*M[10]);

	SetRelativeScale3D(FVector(Sx, Sy, Sz));
}

void UUDComponent::LoadPointCloud()
{
	if (PointCloudHandle)
		return;

	UUDSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UUDSubsystem>();

	if (!MySubsystem)
		return;

	if (Url.IsEmpty())
		return;

	PointCloudHandle = MySubsystem->Load(GetUrl());

	if (PointCloudHandle)
		UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Component %s | Load PCI | %p | %s"), *GetName(), PointCloudHandle, *PointCloudHandle->URL);
}

void UUDComponent::UnloadPointCloud()
{
	if (!PointCloudHandle)
		return;

	UUDSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UUDSubsystem>();
	if (!MySubsystem)
	{
		PointCloudHandle = nullptr;
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Component %s | Unload PCI | %p | %s"), *GetName(), PointCloudHandle, *PointCloudHandle->URL);

	MySubsystem->Remove(PointCloudHandle);
	PointCloudHandle = nullptr;
}

void UUDComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadPointCloud();
}

void UUDComponent::BeginDestroy()
{
	if (PointCloudHandle)
		UnloadPointCloud();

	Super::BeginDestroy();
}

void UUDComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PointCloudHandle)
		UnloadPointCloud();

	Super::EndPlay(EndPlayReason);
}

void UUDComponent::PostLoad()
{
	Super::PostLoad();

	LoadPointCloud();
}

FPrimitiveSceneProxy* UUDComponent::CreateSceneProxy()
{
	return new FPointCloudSceneProxy(this);
}

#if WITH_EDITOR
void UUDComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (!PropertyChangedEvent.Property)
	{
		return;
	}

	FName PropName = PropertyChangedEvent.Property->GetFName();
	FString PropNameAsString = PropertyChangedEvent.Property->GetName();
	if (PropName == GET_MEMBER_NAME_CHECKED(UUDComponent, Url))
	{
		UnloadPointCloud();
		LoadPointCloud();
	}
}
#endif //WITH_EDITOR
