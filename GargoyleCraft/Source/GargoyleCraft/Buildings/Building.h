#pragma once
#include "GargoyleCraft/Golems/Data/PDA_Golem.h"

#include "Building.generated.h"

class USceneComponent;
class UArrowComponent;

UCLASS()
class GARGOYLECRAFT_API ABuilding : public AActor, public ISelectable
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
    void RequestGolemCreation(TSoftObjectPtr<UPDA_Golem> Data);

	//SelectableInterface
	virtual AActor* Selected_Implementation(AGC_PC_RTS* PlayerController) override;
	virtual AActor* Unselected_Implementation(AGC_PC_RTS* PlayerController) override;
};