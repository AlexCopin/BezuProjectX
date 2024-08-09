#pragma once

#include "UObject/Interface.h"
#include "Selectable.generated.h"

class AGC_PC_RTS;

UINTERFACE(MinimalAPI, Blueprintable)
class USelectable : public UInterface
{
	GENERATED_BODY()
};

class ISelectable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* Selected(AGC_PC_RTS* PlayerController);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* Unselected(AGC_PC_RTS* PlayerController);
};