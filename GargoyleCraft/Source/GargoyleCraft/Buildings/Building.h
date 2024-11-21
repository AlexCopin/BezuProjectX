#pragma once
#include "GargoyleCraft/Golems/Data/PDA_Golem.h"
#include "GargoyleCraft/Actors/GC_Actor.h"

#include "Building.generated.h"

struct FPlayerData;
class USceneComponent;
class UArrowComponent;

UCLASS()
class GARGOYLECRAFT_API ABuilding : public AGC_Actor, public ISelectable
{
  GENERATED_BODY()
public:
  ABuilding();

	virtual void BeginPlay() override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USceneComponent> Root;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
    TObjectPtr<UArrowComponent> GolemSpawnPoint;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UArrowComponent> GolemSpawnFlag;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<UPDA_Golem>> GolemPool;
  UFUNCTION(BlueprintCallable)
    bool RequestGolemCreation(TSoftObjectPtr<UPDA_Golem> Data);

	//SelectableInterface
	virtual AActor* Selected_Implementation(AGC_PC_RTS* PlayerController) override;
	virtual AActor* Unselected_Implementation(AGC_PC_RTS* PlayerController) override;

	//Initializable
	virtual void Initialize_Implementation(FPlayerData DataSent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Creation")
	FGameplayTag ResourceTag;
};