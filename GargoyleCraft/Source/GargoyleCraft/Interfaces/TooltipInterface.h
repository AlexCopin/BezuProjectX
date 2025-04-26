#pragma once

#include "GargoyleCraft/Tooltip/GC_TooltipManager.h"
#include "UObject/Interface.h"
#include "TooltipInterface.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UTooltipInterface : public UInterface
{
	GENERATED_BODY()
};

class ITooltipInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTooltipData GetTooltip(UObject* WorldContext);
};