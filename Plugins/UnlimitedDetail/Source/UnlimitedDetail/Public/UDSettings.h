#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UDSettings.generated.h"

/**
 * Settings for the Unlimited Detail (udSDK) plugin.
 * Stored in DefaultUnlimitedDetail.ini; appears in Project Settings > Plugins > Unlimited Detail.
 */
UCLASS(config = UnlimitedDetail, defaultconfig, meta = (DisplayName = "Unlimited Detail (udSDK)"))
class UNLIMITEDDETAIL_API UUDSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// UDeveloperSettings interface — places this section under Project > Plugins
	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
	virtual FText GetSectionText() const override
	{
		return NSLOCTEXT("UDSettings", "SectionText", "Unlimited Detail (udSDK)");
	}
	virtual FText GetSectionDescription() const override
	{
		return NSLOCTEXT("UDSettings", "SectionDesc", "Settings for the Unlimited Detail (udSDK) point cloud plugin.");
	}

	UPROPERTY(config, EditAnywhere, Category = "Unlimited Detail", meta = (ToolTip = "udSDK server URL"))
	FString ServerPath;

	UPROPERTY(config, EditAnywhere, Category = "Unlimited Detail", meta = (ToolTip = "udSDK API key"))
	FString APIKey;
};
