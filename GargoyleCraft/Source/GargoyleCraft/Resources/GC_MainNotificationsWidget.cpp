// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_MainNotificationsWidget.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>

void UGC_MainNotificationsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(auto PD = GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>())
	{
		PD->OnResourceUpdated.AddDynamic(this, &UGC_MainNotificationsWidget::NotifyResourceUpdated);
		PD->OnArmyUpdated.AddDynamic(this, &UGC_MainNotificationsWidget::NotifyArmyUpdated);
	}
}

void UGC_MainNotificationsWidget::NotifyResourceUpdated_Implementation(FGameplayTag ResourceTag, int NewValue, int ChangeValue)
{
	//DoShits, in BP too
}

void UGC_MainNotificationsWidget::NotifyArmyUpdated_Implementation(UPDA_Golem* GolemConcerned, bool bAdded, FArmyData ArmyData)
{
	//DoShits, in BP too
}
