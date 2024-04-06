#pragma once
#include "AbilitySystemComponent.h"

#include "GC_AbilitySystemComponent.generated.h"

UCLASS()
class GARGOYLECRAFT_API UGC_AbilitySystemComponent : public UAbilitySystemComponent
{
  GENERATED_BODY()
public:
  void Init();
  UFUNCTION()
  void ApplyDefaultValues();
};