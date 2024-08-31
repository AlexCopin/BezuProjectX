// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayAbilities/GC_GameplayAbility_Character.h"
#include "GA_BasicMelee.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGA_BasicMelee : public UGC_GameplayAbility_Character
{
	GENERATED_BODY()
public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	FTimerHandle CheckTarget;
};
