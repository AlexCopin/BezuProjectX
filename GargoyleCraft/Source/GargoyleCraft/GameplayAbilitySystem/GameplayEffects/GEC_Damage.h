// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEC_Damage.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGEC_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
