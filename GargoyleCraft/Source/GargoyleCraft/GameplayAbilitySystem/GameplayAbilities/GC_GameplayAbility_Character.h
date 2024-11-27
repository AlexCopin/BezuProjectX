// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayAbilities/GC_GameplayAbility.h"
#include <Abilities/Tasks/AbilityTask_PlayMontageAndWait.h>
#include "GC_GameplayAbility_Character.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGC_GameplayAbility_Character : public UGC_GameplayAbility
{
	GENERATED_BODY()
public:
	UGC_GameplayAbility_Character();

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	TObjectPtr<UAnimSequence> AnimSequence;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AnimMontage;

	UAbilityTask_PlayMontageAndWait* PlayAnimTask;

	UFUNCTION()
	virtual void OnAnimCompleted();
	UFUNCTION()
	virtual void OnAnimCancelled();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void SetDuration() override;
	virtual void DurationEnded() override;
};
