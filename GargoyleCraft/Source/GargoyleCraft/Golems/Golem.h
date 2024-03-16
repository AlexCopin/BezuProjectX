#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GargoyleCraft/Components/Golem/C_Pool.h"
#include "Golem.generated.h"

UCLASS()
class AGolem : public ACharacter
{
    GENERATED_BODY()
public:
  AGolem();
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TObjectPtr<USceneComponent> Root;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UC_Pool> PoolComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};