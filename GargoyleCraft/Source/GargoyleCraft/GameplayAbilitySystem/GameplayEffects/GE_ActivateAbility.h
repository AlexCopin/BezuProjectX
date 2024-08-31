// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_ActivateAbility.generated.h"

/**
 *
 */
UCLASS()
class GARGOYLECRAFT_API UGE_ActivateAbility : public UGameplayEffect
{
	GENERATED_BODY()
	UGE_ActivateAbility();
	virtual void PostInitProperties() override;
};
