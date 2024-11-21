#include "GC_Actor.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>
#include <GargoyleCraft/BlueprintFunctionLibraries/AbilityTools.h>

void AGC_Actor::BeginPlay()
{
	Super::BeginPlay(); 
	if (GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->IsInitialized)
		Execute_Initialize(this, GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->PlayerData);
	else
		GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->OnDataInitialized.AddDynamic(this, &AGC_Actor::Initialize);
}


void AGC_Actor::Initialize_Implementation(FPlayerData DataSent)
{
	if (Initialized)
		return;
	IInitializable::Initialize_Implementation(DataSent);
	Initialized = true;
	GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->OnDataInitialized.RemoveDynamic(this, &AGC_Actor::Initialize);
	GetWorld()->GetTimerManager().SetTimer(TimerCustomTick, this, &AGC_Actor::CustomTick, CustomTickDelay, true);
}

void AGC_Actor::CustomTick_Implementation()
{

}

void AGC_Actor::ActivateCustomTick(bool Activate)
{
	bActivateCustomTick = Activate;
	if (Activate)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerCustomTick, this, &AGC_Actor::CustomTick, CustomTickDelay, true);
	}
	else {
		GetWorld()->GetTimerManager().ClearTimer(TimerCustomTick);
	}
}