#pragma once

#include "GargoyleCraft/Include/GC_Structs.h"
#include "GC_GameInstance.generated.h"

UCLASS()
class UGC_GameInstance : public UGameInstance
{
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPlayerData PlayerData;
};