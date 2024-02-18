#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Golem.generated.h"

UCLASS()
class AGolem : public AActor
{
    GENERATED_BODY()
public:
  AGolem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};