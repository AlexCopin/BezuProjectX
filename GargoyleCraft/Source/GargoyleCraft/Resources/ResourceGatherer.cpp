#include "ResourceGatherer.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>
#include <GargoyleCraft/BlueprintFunctionLibraries/AbilityTools.h>

void AResourceGatherer::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerScan, this, &AResourceGatherer::Scan, ScanDelay, true);
}

void AResourceGatherer::BeginConstruct()
{
	GetWorld()->GetTimerManager().SetTimer(TimerConstruction, this, &AResourceGatherer::FinishConstruct, ConstructionDuration, false);
	GetWorld()->GetTimerManager().ClearTimer(TimerScan);
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
	UE_LOG(LogTemp, Warning, TEXT("Terminate Resource Gatherer (Empty)"));
}

void AResourceGatherer::Scan_Implementation() 
{
	if (auto golem = UAbilityTools::FindNearestGolem(this, this, { EGolemAllegiance::Ally }, RangeScan)) 
	{
		OnGolemScanned.Broadcast(true);
	}
	else 
	{
		OnGolemScanned.Broadcast(false);
	}
}