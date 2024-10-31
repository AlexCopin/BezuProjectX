// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/DataAssets/PDA_Generic.h"
#include "PDA_Resource.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UPDA_Resource : public UPDA_Generic
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Max = 500;
};
