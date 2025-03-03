// Fill out your copyright notice in the Description page of Project Settings.


#include "GargoyleCraft/HUD/GC_HUD.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>
#include <GargoyleCraft/Resources/GC_MainNotificationsWidget.h>

void AGC_HUD::BeginPlay()
{
	if (GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->IsInitialized)
		Execute_Initialize(this, GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->PlayerData);
	else
		GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->OnDataInitialized.AddDynamic(this, &AGC_HUD::Initialize);
}

void AGC_HUD::Initialize_Implementation(FPlayerData DataSent)
{
	MainDynamicResourceWidget = CreateWidget<UGC_MainNotificationsWidget>(GetOwningPlayerController(), MainDynamicResourceWidgetClass);
	MainDynamicResourceWidget->AddToViewport();
}
