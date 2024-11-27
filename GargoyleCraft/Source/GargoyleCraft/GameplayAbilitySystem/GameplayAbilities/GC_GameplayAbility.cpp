// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_GameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayAbilities/GE_Cooldown_BasicMelee.h"
#include "GargoyleCraft/GameplayAbilitySystem/Data/PDA_GameplayAbility.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_ActivateAbility.h"

void UGC_GameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* _ActorInfo, const FGameplayAbilitySpec& _Spec)
{
  Super::OnGiveAbility(_ActorInfo, _Spec);
}

void UGC_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GCAbilitySystemComponent = Cast<UGC_AbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	//Effect du cul
	CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, true);
	AbilityData = GCAbilitySystemComponent->GetAbilityDataFromSpecHandle(GetCurrentAbilitySpecHandle());
}

void UGC_GameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		auto context = MakeEffectContext(Handle, ActorInfo);
		auto spec = GCAbilitySystemComponent->MakeOutgoingSpec(CooldownGE->GetClass(), 1, context);
		auto abilityData = GCAbilitySystemComponent->GetAbilityDataFromSpecHandle(GetCurrentAbilitySpecHandle())->AbilityData;
		spec.Data->SetSetByCallerMagnitude(abilityData.CooldownTag, abilityData.Cooldown);
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, spec);
	}
}

void UGC_GameplayAbility::DurationEnded()
{
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGC_GameplayAbility::SetDuration()
{
	float duration = AbilityData->AbilityData.Duration;
	GetWorld()->GetTimerManager().SetTimer(DurationHandle, this, &UGC_GameplayAbility::DurationEnded, duration);
}
