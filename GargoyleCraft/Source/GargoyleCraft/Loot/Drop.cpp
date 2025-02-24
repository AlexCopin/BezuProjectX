// Fill out your copyright notice in the Description page of Project Settings.


#include "Drop.h"
#include "Kismet/GameplayStatics.h"
#include <GargoyleCraft/BlueprintFunctionLibraries/AbilityTools.h>
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>

// Sets default values
ADrop::ADrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADrop::BeginPlay()
{
	Super::BeginPlay();
}

void ADrop::ConsumeDrop_Implementation()
{
	//Do whatever is needed in BP for animation / FX 
	GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->TryAddConsumableTag(_LootData);
	bIsConsumed = true;
}

void ADrop::Initialize_Implementation(FPlayerData DataSent)
{
	Super::Initialize_Implementation(DataSent);
}

void ADrop::Init(const FLootData& LootData)
{
	_LootData = LootData;
}

void ADrop::CustomTick_Implementation()
{
	Super::CustomTick_Implementation();
	if(!bIsConsumed)
	{
		if (auto golem = UAbilityTools::FindNearestGolem(this, this, { EGolemAllegiance::Ally }, RangeScan))
		{
			ConsumeDrop();
		}
	}
}
