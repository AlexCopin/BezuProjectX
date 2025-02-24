#pragma once
#include <GargoyleCraft/Loot/Drop.h>
#include "C_Drop.generated.h"

UCLASS()
class UC_Drop : public UActorComponent
{
  GENERATED_BODY()
public:
  
  virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
  TArray<FLootData> Loots;
  UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
  TSubclassOf<ADrop> DropClass;

  UFUNCTION()
  void SpawnLoot();
};