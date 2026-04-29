// Copyright Epic Games, Inc. All Rights Reserved.

#include "UdSDKEditor.h"
#include "UDSubsystem.h"
#include "UDComponent.h"
#include "Editor.h"
#include "EditorViewportClient.h"
#include "Framework/Application/SlateApplication.h"
#include "Containers/Ticker.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

// Intercepts left mouse-button clicks in Slate so we can run a deferred depth
// comparison between the UD pick result and whatever UE's normal hit-proxy
// system selected.  The event is never consumed here — UE always sees it too.
class FUDPickingInputPreProcessor : public IInputProcessor
{
public:
	bool bMouseDownPending = false;
	bool bClickPending = false;
	bool bAddToSelection = false;

	virtual void Tick(const float /*DeltaTime*/, FSlateApplication& /*SlateApp*/, TSharedRef<ICursor> /*Cursor*/) override {}

	virtual bool HandleMouseButtonDownEvent(FSlateApplication& /*SlateApp*/, const FPointerEvent& MouseEvent) override
	{
		if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && !MouseEvent.IsAltDown())
		{
			bMouseDownPending = true;
			bAddToSelection = MouseEvent.IsControlDown();
		}
		return false;
	}

	virtual bool HandleMouseButtonUpEvent(FSlateApplication& /*SlateApp*/, const FPointerEvent& MouseEvent) override
	{
		// Require a matching DOWN to filter out synthetic UPs and drag-ends.
		// Detect on UP so our tick fires after UE's hit-proxy ProcessClick (which would
		// otherwise call SelectNone and overwrite our selection).
		if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && bMouseDownPending)
		{
			bMouseDownPending = false;
			bClickPending = true;
		}
		return false;
	}
};

// ──────────────────────────────────────────────────────────────────────────────

void FUdSDKEditorModule::StartupModule()
{
	InputPreProcessor = MakeShared<FUDPickingInputPreProcessor>();
	FSlateApplication::Get().RegisterInputPreProcessor(InputPreProcessor);

	TickHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateRaw(this, &FUdSDKEditorModule::Tick));
}

void FUdSDKEditorModule::ShutdownModule()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);

	if (FSlateApplication::IsInitialized())
		FSlateApplication::Get().UnregisterInputPreProcessor(InputPreProcessor);

	InputPreProcessor.Reset();
}

bool FUdSDKEditorModule::Tick(float /*DeltaTime*/)
{
	if (InputPreProcessor && InputPreProcessor->bClickPending)
	{
		InputPreProcessor->bClickPending = false;
		HandleEditorPick();
	}
	return true; // Keep ticking
}

void FUdSDKEditorModule::HandleEditorPick()
{
	// Only run in the editor world, not PIE.
	if (!GEditor || GEditor->PlayWorld)
		return;

	UUDSubsystem* Subsystem = GEngine->GetEngineSubsystem<UUDSubsystem>();
	if (!Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Pick: no subsystem"));
		return;
	}

	FUDPickResult UDResult = Subsystem->GetLastPickResult();
	if (!UDResult.bHit)
	{
		UE_LOG(LogTemp, Verbose, TEXT("UnlimitedDetail | Pick: no UD hit at cursor"));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Pick: UD hit at %s, camera %s"), *UDResult.WorldPosition.ToString(), *UDResult.CameraPosition.ToString());

	UUDComponent* UDComponent = UDResult.Component.Get();
	if (!UDComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Pick: UD hit but component is null"));
		return;
	}

	// Find the active level-editor viewport client.
	FViewport* ActiveViewport = GEditor->GetActiveViewport();
	if (!ActiveViewport)
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Pick: no active viewport"));
		return;
	}

	FEditorViewportClient* VpClient = static_cast<FEditorViewportClient*>(ActiveViewport->GetClient());
	if (!VpClient)
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Pick: no viewport client"));
		return;
	}

	// Only interfere with the main editor world viewport, not material/mesh previews.
	UWorld* VpWorld = VpClient->GetWorld();
	UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
	if (VpWorld != EditorWorld)
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Pick: viewport world (%s) != editor world (%s)"),
			VpWorld ? *VpWorld->GetName() : TEXT("null"),
			EditorWorld ? *EditorWorld->GetName() : TEXT("null"));
		return;
	}

	// Build a ray from the stored camera position through the UD hit point.
	// Because the UD pick was taken at the cursor this is the correct cursor ray —
	// no need to deproject from screen coordinates separately.
	const FVector RayOrigin = UDResult.CameraPosition;
	const FVector RayDir = (UDResult.WorldPosition - RayOrigin).GetSafeNormal();

	if (RayDir.IsNearlyZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("UnlimitedDetail | Pick: degenerate ray (hit pos == camera pos)"));
		return;
	}

	// Trace against UE geometry to find the closest opaque hit along the same ray.
	FHitResult UEHit;
	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(UDEditorPick), true);
	const bool bUEHit = EditorWorld->LineTraceSingleByChannel(
		UEHit,
		RayOrigin,
		RayOrigin + RayDir * 100000000.0f,
		ECC_Visibility,
		QueryParams);

	const float UEDist = bUEHit ? UEHit.Distance : TNumericLimits<float>::Max();
	const float UDDist = FVector::Dist(RayOrigin, UDResult.WorldPosition);

	UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Pick: UDDist=%.1f UEDist=%.1f"), UDDist, UEDist);

	if (UDDist < UEDist)
	{
		// The UD voxel is in front of any UE geometry — select its owning actor.
		AActor* OwnerActor = UDComponent->GetOwner();
		if (OwnerActor)
		{
			UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Pick: selecting actor %s"), *OwnerActor->GetName());

			if (!InputPreProcessor->bAddToSelection)
				GEditor->SelectNone(false, true);

			GEditor->SelectActor(OwnerActor, true, true);
			GEditor->NoteSelectionChange();
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | Pick: UE geometry is closer, deferring to normal selection"));
	}
	// else: UE geometry is in front; UE's normal hit-proxy selection already handled it.
}

IMPLEMENT_MODULE(FUdSDKEditorModule, UnlimitedDetailEditor)
