// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GC_GameplayAbility.generated.h"

class UGC_AbilitySystemComponent;
class UPDA_GameplayAbility;
/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGC_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
  virtual void OnGiveAbility(const FGameplayAbilityActorInfo* _ActorInfo, const FGameplayAbilitySpec& _Spec) override;
  virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY()
	UGC_AbilitySystemComponent* GCAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UPDA_GameplayAbility> AbilityData;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
protected:
	FTimerHandle DurationHandle;
	UFUNCTION()
	void DurationEnded();
};
