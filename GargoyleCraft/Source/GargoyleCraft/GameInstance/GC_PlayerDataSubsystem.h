// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GC_PlayerDataSubsystem.generated.h"

class UPDA_GameData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataInitialized, FPlayerData, DataSent);
/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGC_PlayerDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//Set from saves (WIP) if here, or Param if not there
	UFUNCTION()
	void SetGameData(UPDA_GameData* InGameData);
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnDataInitialized OnDataInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPDA_GameData> GameData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerData PlayerData;

	UFUNCTION(BlueprintCallable)
	TArray<UPDA_Golem*> GetAvailableGolemsFromGameData();
	UFUNCTION(BlueprintCallable)
	TArray<UPDA_Golem*> GetAvailableGolemsFromPlayerData();
	UFUNCTION(BlueprintCallable)
	bool TryAddGolemInArmy(UPDA_Golem* GolemData);
	UFUNCTION(BlueprintCallable)
	bool RemoveGolemFromArmy(UPDA_Golem* GolemData);
};
