// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "GargoyleCraft/Include/GC_DisplayTypes.h"
#include "PDA_GameData.generated.h"

/**
 * 
 */

UCLASS()
class GARGOYLECRAFT_API UPDA_GameData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    FPlayerData DefaultStartingData;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    TObjectPtr<UDataTable> AvailableGolemTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TObjectPtr<UDataTable> AvailableRecipes;
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Display")
  TObjectPtr<UDataTable> AttributesDisplayValues;

  UFUNCTION(BlueprintCallable)
  FAttributeDisplayData FindAttributeDisplayValue(FGameplayAttribute Attribute);
};
