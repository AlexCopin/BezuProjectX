#include "C_Drop.h"
#include <Kismet/GameplayStatics.h>
#include <GargoyleCraft/Loot/Drop.h>


void UC_Drop::BeginPlay()
{
  Super::BeginPlay();
}

void UC_Drop::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SpawnLoot();
}

void UC_Drop::SpawnLoot()
{
	if (ensure(DropClass))
	{
		for(auto lootData : Loots)
		{
			if (FMath::FRandRange(0.0f, 1.0f) > lootData.DropChance)
				continue;

			auto drop = GetWorld()->SpawnActorDeferred<ADrop>(DropClass, GetOwner()->GetActorTransform());
			drop->Init(lootData);
			UGameplayStatics::FinishSpawningActor(drop, GetOwner()->GetActorTransform());
		}
	}
}