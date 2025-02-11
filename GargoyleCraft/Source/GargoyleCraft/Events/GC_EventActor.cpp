#include "GC_EventActor.h"
#include "GargoyleCraft/Golems/Golem.h"
#include <GargoyleCraft/BlueprintFunctionLibraries/GenericFunctions.h>


AGC_EventActor::AGC_EventActor()
{
	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(Root);
}
void AGC_EventActor::Init(const FMonsterEventData& Data)
{
	EventData = Data;
	int i = 0;
	while(i < EventData.TotalNumberToSpawn)
	{
		float delay = EventData.Duration / EventData.TotalNumberToSpawn;
		float delayOffset = FMath::FRandRange(0.f, EventData.SpawnOffsetMax);
		delay += delayOffset;
		FSpawnData tempData;
		tempData.Delay = delay;
		tempData.SpawnedActor = EventData.SpawnedActors[FMath::RandRange(0, EventData.SpawnedActors.Num() - 1)];
		tempData.Number = FMath::FRandRange(EventData.NumberRange.X, EventData.NumberRange.Y);
		float randomMagnitude = FMath::FRandRange(EventData.SpawnRange.X, EventData.SpawnRange.Y);
		FVector randomDirection = UGenericFunctions::CalculateRandomNormalizedDirectionFromLocation(this, GetActorLocation(), false);
		randomDirection *= randomMagnitude;
		FVector randomPosition = GetActorLocation() + randomDirection;
		tempData.SpawnPosition = randomPosition;
		SpawnDatas.Add(tempData);
		i += tempData.Number;
	}
	if(SpawnDatas.IsValidIndex(0))
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AGC_EventActor::SpawnActor, SpawnDatas[0].Delay, false, SpawnDatas[0].Delay);
}

void AGC_EventActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);
	GetWorld()->GetTimerManager().SetTimer(TimerCustomTick, this, &AGC_EventActor::CustomTick, CustomTickDelay, true);
}
void AGC_EventActor::CustomTick_Implementation()
{
		
}

void AGC_EventActor::ActivateCustomTick(bool Activate)
{
	bActivateCustomTick = Activate;
	if (Activate)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerCustomTick, this, &AGC_EventActor::CustomTick, CustomTickDelay, true);
	}
	else {
		GetWorld()->GetTimerManager().ClearTimer(TimerCustomTick);
	}
}

void AGC_EventActor::SpawnActor()
{
	if (SpawnDatas.IsValidIndex(CurrentSpawnData)) 
	{
		auto spawnData = SpawnDatas[CurrentSpawnData];
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		for(int i = 0; i < spawnData.Number; i++)
		{
			auto Golem = GetWorld()->SpawnActor<AGolem>(spawnData.SpawnedActor, spawnData.SpawnPosition, FRotator::ZeroRotator, spawnParams);
			Golem->UpdateTargetLocation(GetActorLocation());
		}
		CurrentSpawnData++;
		if (SpawnDatas.IsValidIndex(CurrentSpawnData))
			GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AGC_EventActor::SpawnActor, SpawnDatas[CurrentSpawnData].Delay, false, SpawnDatas[CurrentSpawnData].Delay);
		else
			EndEvent();
	}
}

void AGC_EventActor::EndEvent()
{
	ActivateCustomTick(false);
	Destroy();
}
