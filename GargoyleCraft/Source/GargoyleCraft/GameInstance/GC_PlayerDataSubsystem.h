// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "GC_GameInstance.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <GargoyleCraft/Craft/PDA_Blueprint.h>
#include "GC_PlayerDataSubsystem.generated.h"

class UPDA_GameData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataInitialized, FPlayerData, DataSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnArmyUpdated, UPDA_Golem*, GolemConcerned, bool, bAdded, FArmyData, ArmyData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnResourceUpdated, FGameplayTag, ResourceTag, int, NewValue, int, ChangeValue);
/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UGC_PlayerDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//Set from saves (WIP) if here, or Param if not there
	UFUNCTION()
	void SetGameData(UPDA_GameData* InGameData);

	bool IsInitialized = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPDA_GameData> GameData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerData PlayerData;
	UPROPERTY(BlueprintReadOnly)
	UGC_GameInstance* GCGameInstance;
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnDataInitialized OnDataInitialized;
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnArmyUpdated OnArmyUpdated;

	//----------GOLEMS DATA / UNLOCKS
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UPDA_Golem*> GetAvailableGolemsFromGameData();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UPDA_Golem*> GetAvailableGolemsFromPlayerData();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UPDA_Golem*> GetChosenGolemsFromPlayerArmy();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsGolemInPlayerArmy(UPDA_Golem* DAGolem);
	UFUNCTION(BlueprintCallable)
	bool TryAddGolemInArmy(UPDA_Golem* GolemData);
	UFUNCTION(BlueprintCallable)
	bool RemoveGolemFromArmy(UPDA_Golem* GolemData);
	//-------------------

	//-------------------Resources
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FResourceData GetResourceData(FGameplayTag ResourceTag) { return *PlayerData.ResourcesData.Find(ResourceTag); }

	UFUNCTION(BlueprintCallable)
	void AddToResource(FGameplayTag ResourceTag, int Value);
	UFUNCTION(BlueprintCallable)
	bool PayResource(FGameplayTag ResourceTag, int Value);
	UFUNCTION(BlueprintCallable)
	bool IsResourceSufficient(FGameplayTag ResourceTag, int Value);
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnResourceUpdated OnResourceUpdated;

	//-----------------RecipesBlueprints-------
	UFUNCTION(BlueprintCallable)
	void ApplyRecipeOnGolem(AGolem* Golem);
	UFUNCTION(BlueprintCallable)
	bool TryConstructRecipe(FGameplayTag GolemType, UPDA_Blueprint* Recipe);

protected:
	TMap<FGameplayTag, TArray<UPDA_Blueprint*>> Recipes;
};
