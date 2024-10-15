#include "MapInitializer.h"

#include "GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h"
#include "GargoyleCraft/Interfaces/Initializable.h"

void AMapInitializer::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->OnDataInitialized.AddDynamic(this, &AMapInitializer::Init);
}

void AMapInitializer::Init(FPlayerData DataSent)
{
	if (Spawns.IsValidIndex(0))
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this, &AMapInitializer::SpawnEvent, Spawns[0].Delay, false, Spawns[0].Delay);
	}
}

void AMapInitializer::SpawnEvent()
{
	CurrentSpawn = Spawns[spawningIndex];
	Spawn();
	spawningIndex++;
	if(Spawns.IsValidIndex(spawningIndex))
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AMapInitializer::SpawnEvent, Spawns[spawningIndex].Delay, false, Spawns[spawningIndex].Delay);
	}
}

void AMapInitializer::Spawn_Implementation()
{
	if(CurrentSpawn.SpawnPoint)
	{
		auto spawned = GetWorld()->SpawnActor<AActor>(CurrentSpawn.SpawnedActor, CurrentSpawn.SpawnPoint->GetActorTransform(), FActorSpawnParameters());
		if (Cast<IInitializable>(spawned)) 
		{
			Cast<IInitializable>(spawned)->Execute_Initialize(spawned, GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->PlayerData);
		}
	}
}
