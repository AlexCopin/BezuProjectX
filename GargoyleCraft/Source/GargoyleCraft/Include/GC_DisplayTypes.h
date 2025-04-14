#pragma once
#include "GargoyleCraft/Tooltip/GC_TooltipManager.h"
#include "GC_DisplayTypes.generated.h"

USTRUCT(BlueprintType)
struct FAttributeDisplayData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FTooltipData TooltipData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString RawName = "Attribute";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsHidden = false;
};