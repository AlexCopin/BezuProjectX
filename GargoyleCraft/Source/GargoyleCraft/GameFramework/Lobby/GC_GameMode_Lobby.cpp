// Fill out your copyright notice in the Description page of Project Settings.


#include "GargoyleCraft/GameFramework/Lobby/GC_GameMode_Lobby.h"

#include "GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h"


void AGC_GameMode_Lobby::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->SetGameData(DefaultGameData);
}
