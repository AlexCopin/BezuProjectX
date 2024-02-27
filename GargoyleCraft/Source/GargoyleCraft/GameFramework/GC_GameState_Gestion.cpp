#include "GC_GameState_Gestion.h"

#include "GargoyleCraft/GameData/PDA_GameData.h"
#include "GargoyleCraft/GameInstance/GC_GameInstance.h"

void AGC_GameState_Gestion::BeginPlay()
{
  Super::BeginPlay();
  GET_GAMEINSTANCE_GC()->PlayerData = DefaultGameData->DefaultStartingData;
}
