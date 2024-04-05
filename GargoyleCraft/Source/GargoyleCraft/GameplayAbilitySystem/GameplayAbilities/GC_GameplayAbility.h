// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GC_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGC_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
  virtual void OnGiveAbility(const FGameplayAbilityActorInfo* _ActorInfo, const FGameplayAbilitySpec& _Spec) override;
};
