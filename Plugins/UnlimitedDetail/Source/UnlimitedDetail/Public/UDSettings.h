#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UDSettings.generated.h"

UCLASS(config = UnlimitedDetail, defaultconfig)
class UNLIMITEDDETAIL_API UUDSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "UnlimitedDetail", meta = (ToolTip = ""))
	FString ServerPath;

	UPROPERTY(config, EditAnywhere, Category = "UnlimitedDetail", meta = (ToolTip = ""))
	FString APIKey;
};
