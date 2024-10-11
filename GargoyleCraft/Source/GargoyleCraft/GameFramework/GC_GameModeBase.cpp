#include "GC_GameModeBase.h"
#include "GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h"


void AGC_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->SetGameData(DefaultGameData);
}
