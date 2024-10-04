#pragma once

#include "GargoyleCraft/Include/GC_Structs.h"
#include "GC_GameInstance.generated.h"

#define GET_GAMEINSTANCE_GC() (GetGameInstance<UGC_GameInstance>())


UCLASS()
class UGC_GameInstance : public UGameInstance
{
  GENERATED_BODY()
};