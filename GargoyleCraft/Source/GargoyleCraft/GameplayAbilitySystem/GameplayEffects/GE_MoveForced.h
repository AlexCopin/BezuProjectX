// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_MoveForced.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGE_MoveForced : public UGameplayEffect
{
	GENERATED_BODY()
	UGE_MoveForced();
	virtual void PostInitProperties() override;
};
