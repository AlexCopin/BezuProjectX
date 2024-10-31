// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "GargoyleCraft/DataAssets/PDA_Generic.h"
#include "PDA_GameplayAbility.generated.h"

class UGameplayAbility;

UCLASS()
class GARGOYLECRAFT_API UPDA_GameplayAbility : public UPDA_Generic
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability|Data")
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability|Data")
	FAbilityData AbilityData;
};
