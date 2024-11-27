// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GC_ATask_PlayMontageWait.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGC_ATask_PlayMontageWait : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()
	
	virtual void Activate() override;

};
