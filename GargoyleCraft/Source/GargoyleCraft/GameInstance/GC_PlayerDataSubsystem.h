// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "GC_GameInstance.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <GargoyleCraft/Craft/PDA_Recipe.h>
#include "GC_PlayerDataSubsystem.generated.h"

class UPDA_GameData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataInitialized, FPlayerData, DataSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnArmyUpdated, UPDA_Golem*, GolemConcerned, bool, bAdded, FArmyData, ArmyData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnResourceUpdated, FGameplayTag, ResourceTag, int, NewValue, int, ChangeValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroUpdated, FHeroData, HeroData);
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
	//---------------------------------------------------

	//-----------------RecipesBlueprints-------
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UPDA_Recipe*> GetAvailableRecipesFromGameData();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UPDA_Recipe*> GetAvailableRecipesFromPlayerData();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPDA_Recipe* GetRecipeData(FGameplayTag RecipeTag);

	UFUNCTION(BlueprintCallable)
	bool TryAddRecipeToPlayerData(FGameplayTag RecipeTag);
	UFUNCTION(BlueprintCallable)
	void ApplyRecipeOnGolem(AGolem* Golem);
	UFUNCTION(BlueprintCallable)
	bool TryConstructRecipe(FGameplayTag GolemType, UPDA_Recipe* Recipe);
	UFUNCTION(BlueprintCallable)
	bool IsResourceSufficientForRecipe(UPDA_Recipe* Recipe);
	//---------------------------------------------------

	UFUNCTION(BlueprintCallable)
	void TryAddConsumableTag(const FLootData& ConsumableData);

	//-----------Tooltip Generic--------------
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTooltipData GetSimpleTooltip(FGameplayTag DataTag);
	//----------------------------------------


	//---------------------Hero---------------------------
	UPDA_HeroPart* GetHeroPartData(FGameplayTag HeroPartTag);
	int GetHeroPartNumberAvailable(FGameplayTag HeroPartTag);

	UFUNCTION(BlueprintCallable)
	bool TryConstructHeroPart(FGameplayTag HeroPartTag);
	UFUNCTION(BlueprintCallable)
	bool TryApplyHeroPart(FGameplayTag HeroPartTag);

	UPROPERTY(BlueprintAssignable)
	FOnHeroUpdated OnHeroUpdated;
	//----------------------------------------------------

protected:
	TMap<FGameplayTag, FGameplayTagContainer> Recipes;
};
