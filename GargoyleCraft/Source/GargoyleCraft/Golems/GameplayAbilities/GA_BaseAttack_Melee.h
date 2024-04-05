#pragma once

#include "GargoyleCraft/GameplayAbilitySystem/GameplayAbilities/GC_GameplayAbility_Character.h"

#include "GA_BaseAttack_Melee.generated.h"

UCLASS()
class GARGOYLECRAFT_API UGA_BaseAttack_Melee : public UGC_GameplayAbility_Character
{
  GENERATED_BODY()
public:
  virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};