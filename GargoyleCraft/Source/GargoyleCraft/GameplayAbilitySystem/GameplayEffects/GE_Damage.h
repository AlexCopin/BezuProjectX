// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_Damage.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGE_Damage : public UGameplayEffect
{
	GENERATED_BODY()
	UGE_Damage();

	virtual void PostInitProperties() override;
};
