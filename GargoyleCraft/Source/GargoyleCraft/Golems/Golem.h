#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GargoyleCraft/Components/Golem/C_Pool.h"
#include "AbilitySystemInterface.h"
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"
#include "Golem.generated.h"

UCLASS()
class AGolem : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()
public:
  AGolem();
  UFUNCTION()
    void Init();
  virtual void BeginPlay() override;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TObjectPtr<USceneComponent> Root;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UC_Pool> PoolComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TObjectPtr<UGC_AbilitySystemComponent> AbilitySystemComponent;


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
      bool bIsSelected;

    UFUNCTION(BlueprintCallable)
      void UpdateTargetLocation(FVector NewTargetLocation);
    UFUNCTION(BlueprintCallable)
      FVector GetCurrentTargetLocation() { return CurrentTargetLocation; }

  //AbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
private:
    FVector CurrentTargetLocation;
};