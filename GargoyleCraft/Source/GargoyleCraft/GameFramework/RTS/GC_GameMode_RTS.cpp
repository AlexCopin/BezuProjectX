// Fill out your copyright notice in the Description page of Project Settings.


#include "GargoyleCraft/GameFramework/RTS/GC_GameMode_RTS.h"

#include "GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h"


void AGC_GameMode_RTS::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->SetGameData(DefaultGameData);
}
