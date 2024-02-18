// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "CG_PlayerDataSubsystem.generated.h"

USTRUCT()
struct FPlayerData 
{
};

UCLASS()
class GARGOYLECRAFT_API UGC_PlayerDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
  FPlayerData PlayerData;
};
