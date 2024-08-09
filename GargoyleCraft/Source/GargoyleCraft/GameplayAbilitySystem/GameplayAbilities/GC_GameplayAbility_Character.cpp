// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_GameplayAbility_Character.h"

#include "GameplayTagsManager.h"
#include "GargoyleCraft/Include/GC_Macros.h"

UGC_GameplayAbility_Character::UGC_GameplayAbility_Character()
{
	ActivationBlockedTags.AddTag(MAKE_TAG("State.Moving.Forced"));
	ActivationBlockedTags.AddTag(MAKE_TAG("State.Stun"));
	ActivationBlockedTags.AddTag(MAKE_TAG("State.Dead"));
	TargetBlockedTags.AddTag(MAKE_TAG("State.Moving.Forced"));
	TargetBlockedTags.AddTag(MAKE_TAG("State.Stun"));
	TargetBlockedTags.AddTag(MAKE_TAG("State.Dead"));
}

void UGC_GameplayAbility_Character::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                    const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
