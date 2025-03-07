// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericFunctions.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGenericFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FVector CalculateRandomNormalizedDirectionFromLocation(const UObject* WorldContextObject, const FVector& Location, bool IsGround = true);
};
