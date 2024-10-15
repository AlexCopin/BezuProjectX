#pragma once

#include "GargoyleCraft/Include/GC_Structs.h"
#include "UObject/Interface.h"
#include "Initializable.generated.h"

class AGC_PC_RTS;

UINTERFACE(MinimalAPI, Blueprintable)
class UInitializable : public UInterface
{
	GENERATED_BODY()
};

class IInitializable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Initialize(FPlayerData DataSent);
};