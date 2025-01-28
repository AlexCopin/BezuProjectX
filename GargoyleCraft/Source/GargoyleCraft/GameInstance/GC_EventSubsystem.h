// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "GC_EventSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGC_EventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	//if NewDuration == -1 take EventData value
	UFUNCTION(BlueprintCallable)
	void LaunchMonsterEvent(FMonsterEventData Data, FVector CenterLocation, float NewDuration = -1);


};
