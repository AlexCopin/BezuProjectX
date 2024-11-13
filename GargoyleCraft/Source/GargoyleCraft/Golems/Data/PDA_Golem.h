// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/Golems/Golem.h"
#include "Engine/Texture2D.h"
#include "GargoyleCraft/DataAssets/PDA_DefaultActorData.h"
#include "PDA_Golem.generated.h"


/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UPDA_Golem : public UPDA_DefaultActorData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	FGameplayTagContainer RequirementsTags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	FGameplayTag GolemTypeTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	FGameplayTagContainer GolemTags;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    TSubclassOf<AGolem> GolemClass;

	UFUNCTION(BlueprintPure)
	int32 GetCost();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	int32 BaseCost = 30;
};
