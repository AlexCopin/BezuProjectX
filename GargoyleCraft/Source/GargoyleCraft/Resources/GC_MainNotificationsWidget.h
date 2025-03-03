// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/Widgets/GC_Widget.h"
#include <GameplayTagContainer.h>
#include <GargoyleCraft/Include/GC_Structs.h>
#include <GargoyleCraft/Golems/Data/PDA_Golem.h>

#include "GC_MainNotificationsWidget.generated.h"

/**
 *
 */
UCLASS()
class GARGOYLECRAFT_API UGC_MainNotificationsWidget : public UGC_Widget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintNativeEvent)
	void NotifyResourceUpdated(FGameplayTag ResourceTag, int NewValue, int ChangeValue);
	void NotifyResourceUpdated_Implementation(FGameplayTag ResourceTag, int NewValue, int ChangeValue);

	UFUNCTION(BlueprintNativeEvent)
	void NotifyArmyUpdated(UPDA_Golem* GolemConcerned, bool bAdded, FArmyData ArmyData);
	void NotifyArmyUpdated_Implementation(UPDA_Golem* GolemConcerned, bool bAdded, FArmyData ArmyData);

};