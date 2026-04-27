// Copyright Epic Games, Inc. All Rights Reserved.

#include "UDModule.h"

#include <udContext.h>

#include "Interfaces/IPluginManager.h"
#include "CoreMinimal.h"

#define LOCTEXT_NAMESPACE "FUDModule"

// Called when the module is loaded by the engine
void FUDModule::StartupModule()
{
	UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | StartupModule()"));
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("UnlimitedDetail"));
	if (!Plugin.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("UnlimitedDetail | Failed to find plugin — shader directory not registered"));
		return;
	}
	FString PluginShaderDir = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugins/UnlimitedDetail"), PluginShaderDir);
}

void FUDModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("UnlimitedDetail | ShutdownModule()"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUDModule, UnlimitedDetail)