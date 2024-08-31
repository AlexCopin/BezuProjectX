// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BasicMelee.h"

void UGA_BasicMelee::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	//GetWorld()->GetTimerManager().SetTimer()
}

void UGA_BasicMelee::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
}
