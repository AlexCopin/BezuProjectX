#pragma once
#include "GargoyleCraft/Include/GC_Structs.h"

#include "MapInitializer.generated.h"

UCLASS()
class AMapInitializer : public AActor
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void Init(FPlayerData DataSent);
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<FSpawnData> Spawns;

	UPROPERTY()
	FTimerHandle SpawnTimer;
	UFUNCTION()
	void SpawnEvent();
	UFUNCTION(BlueprintNativeEvent)
	void Spawn();
protected:
	UPROPERTY(BlueprintReadOnly)
	FSpawnData CurrentSpawn;
private:
	int spawningIndex = 0;


};