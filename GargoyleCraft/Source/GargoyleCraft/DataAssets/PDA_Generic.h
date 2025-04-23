// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GargoyleCraft/Tooltip/GC_TooltipManager.h"
#include "GargoyleCraft/Interfaces/TooltipInterface.h"
#include "PDA_Generic.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UPDA_Generic : public UPrimaryDataAsset, public ITooltipInterface
{
	GENERATED_BODY()
	
public:
	//UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	//FTooltipData GetTooltip();

	//virtual FTooltipData GetTooltip_Implementation() { return TooltipData; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tooltip")
	FTooltipData TooltipData;

	//-----TooltipInterface
	virtual FTooltipData GetTooltip_Implementation() override {
		return TooltipData;
	};
};
