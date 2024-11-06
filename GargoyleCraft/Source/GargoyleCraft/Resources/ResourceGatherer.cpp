#include "ResourceGatherer.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>

void AResourceGatherer::BeginPlay()
{
	Super::BeginPlay();
}

void AResourceGatherer::BeginConstruct()
{
	GetWorld()->GetTimerManager().SetTimer(TimerConstruction, this, &AResourceGatherer::FinishConstruct, ConstructionDuration, false);
	OnConstructionStarted.Broadcast(ConstructionDuration);
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
}