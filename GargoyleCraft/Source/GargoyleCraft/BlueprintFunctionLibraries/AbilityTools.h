// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilityTools.generated.h"

class UAbilitySystemComponent;
enum EGolemAllegiance : uint8;
class AGolem;
/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UAbilityTools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static AGolem* FindNearestGolem(const UObject* WorldContextObject, const AActor* From, TArray<TEnumAsByte<EGolemAllegiance>> AllegiancesToSearch, float Range);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void ApplyDamage(UAbilitySystemComponent* Source, UAbilitySystemComponent* Target, float Value);


	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static	TArray<FVector> CalculateRectanglePoints(FVector StartingPoint, FVector Center, int NumPoints, float Width, float Height, int NumColumns, int NumRows);
};
