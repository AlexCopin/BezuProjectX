#pragma once
#include "GargoyleCraft/Golems/Data/PDA_Golem.h"

#include "Building.generated.h"

class USceneComponent;
class UArrowComponent;

UCLASS()
class GARGOYLECRAFT_API ABuilding : public AActor
{
  GENERATED_BODY()
public:
  ABuilding();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USceneComponent> Root;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
    TObjectPtr<UArrowComponent> GolemSpawnPoint;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UArrowComponent> GolemSpawnFlag;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<UPDA_Golem>> GolemPool;
  UFUNCTION(BlueprintCallable)
    void RequestGolemCreation(UPDA_Golem* Data);
};