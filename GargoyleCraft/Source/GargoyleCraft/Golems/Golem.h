#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Golem.generated.h"

UCLASS()
class AGolem : public AActor
{
public:
  AGolem();

  TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};