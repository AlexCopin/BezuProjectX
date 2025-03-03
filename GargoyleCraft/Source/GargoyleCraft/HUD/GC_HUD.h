// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <GargoyleCraft/Widgets/GC_Widget.h>
#include "GargoyleCraft/Interfaces/Initializable.h"
#include <GargoyleCraft/Resources/GC_MainNotificationsWidget.h>

#include "GC_HUD.generated.h"

struct FPlayerData;

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API AGC_HUD : public AHUD, public IInitializable
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UGC_MainNotificationsWidget> MainDynamicResourceWidgetClass;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGC_MainNotificationsWidget> MainDynamicResourceWidget;


	//Initializable
	virtual void Initialize_Implementation(FPlayerData DataSent) override;
	bool Initialized = false;
};
