// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "IAssetTools.h"
#include "Framework/Application/IInputProcessor.h"

class FUDPickingInputPreProcessor;

class FUdSDKEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	bool Tick(float DeltaTime);
	void HandleEditorPick();

	TSharedPtr<FUDPickingInputPreProcessor> InputPreProcessor;
	FTSTicker::FDelegateHandle TickHandle;
};
