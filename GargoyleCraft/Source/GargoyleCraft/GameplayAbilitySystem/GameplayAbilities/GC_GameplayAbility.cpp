// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_GameplayAbility.h"

void UGC_GameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* _ActorInfo, const FGameplayAbilitySpec& _Spec)
{
  Super::OnGiveAbility(_ActorInfo, _Spec);
}

void UGC_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GetWorld()->GetTimerManager().SetTimer(DurationHandle, this, &UGC_GameplayAbility::DurationEnded, Duration);
}

void UGC_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGC_GameplayAbility::DurationEnded()
{
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
