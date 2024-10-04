// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GC_GameMode_Lobby.generated.h"

class UPDA_GameData;
/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API AGC_GameMode_Lobby : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPDA_GameData> DefaultGameData;
};
