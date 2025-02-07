// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GargoyleCraft/Widgets/GC_Widget.h"
#include <GargoyleCraft/Include/GC_Structs.h>
#include "GC_RTS_Hud.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API AGC_RTS_Hud : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGC_Widget>	MainRTSWidget;

	UFUNCTION()
	void OnInitialized(FPlayerData PlayerData);
};
