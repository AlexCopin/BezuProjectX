// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_RTS_Hud.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>

void AGC_RTS_Hud::BeginPlay()
{
	auto playerDataSS = GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>();
	if (!playerDataSS->IsInitialized)
	{
		playerDataSS->OnDataInitialized.AddDynamic(this, &AGC_RTS_Hud::OnInitialized);
	}
	else 
	{
		OnInitialized(playerDataSS->PlayerData);
	}
}

void AGC_RTS_Hud::OnInitialized(FPlayerData PlayerData)
{
	UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), MainRTSWidget);
	if (MyWidget)
		MyWidget->AddToViewport();
}
