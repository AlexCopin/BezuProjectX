// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Golem.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UPDA_Golem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Flavor)
    FText Name;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Flavor)
    FText Description;
};
