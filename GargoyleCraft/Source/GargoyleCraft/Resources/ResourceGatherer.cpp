#include "ResourceGatherer.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>
#include <GargoyleCraft/BlueprintFunctionLibraries/AbilityTools.h>
#include <GargoyleCraft/GameInstance/GC_EventSubsystem.h>

void AResourceGatherer::BeginPlay()
{
	Super::BeginPlay();
}

void AResourceGatherer::BeginConstruct()
{
	GetWorld()->GetTimerManager().SetTimer(TimerConstruction, this, &AResourceGatherer::FinishConstruct, ConstructionDuration, false);
	ActivateCustomTick(true);
	OnConstructionStarted.Broadcast(ConstructionDuration);

	GetWorld()->GetGameInstance()->GetSubsystem<UGC_EventSubsystem>()->LaunchMonsterEvent(EventData, GetActorLocation(), ConstructionDuration);
}

void AResourceGatherer::FinishConstruct()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerConstruction);
	GetWorld()->GetTimerManager().SetTimer(TimerGathering, this, &AResourceGatherer::Gather, DelayBetweenGathering, true);
	OnGatheringStarted.Broadcast(DelayBetweenGathering);
}

void AResourceGatherer::Gather_Implementation()
{
	OnGatheringStarted.Broadcast(DelayBetweenGathering);
	GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->AddToResource(ResourceTag, QuantityResource);
	OnGathered.Broadcast(QuantityResource);
	Counter++;
	if (Counter >= Uses) 
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerGathering);
		Terminate();
	}
}
void AResourceGatherer::Terminate_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Terminate Resource Gatherer (Empty)"));
}

void AResourceGatherer::CustomTick_Implementation()
{
	Super::CustomTick_Implementation();
	bool allyGolemInRange = false;
	if (UAbilityTools::FindNearestGolem(this, this, { EGolemAllegiance::Ally }, RangeScan))
	{
		OnGolemScanned.Broadcast(true);
		allyGolemInRange = true;
	}
	else
	{
		allyGolemInRange = false;
		OnGolemScanned.Broadcast(false);
	}
	if (UAbilityTools::FindNearestGolem(this, this, { EGolemAllegiance::Enemy }, RangeScan) && !allyGolemInRange)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerGathering);
		OnGolemScanned.Broadcast(false);
		OnProcessHalted.Broadcast();
	}
}