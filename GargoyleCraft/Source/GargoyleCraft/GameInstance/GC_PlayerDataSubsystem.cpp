// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_PlayerDataSubsystem.h"

#include "GargoyleCraft/GameData/PDA_GameData.h"
#include "GargoyleCraft/Resources/PDA_Resource.h"

void UGC_PlayerDataSubsystem::Initialize(FSubsystemCollectionBase& Collection) 
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("PlayerDataSubsystem : Initialize"));
	GCGameInstance = Cast<UGC_GameInstance>(GetGameInstance());
}

void UGC_PlayerDataSubsystem::SetGameData(UPDA_GameData* InGameData)
{
	//if no saves
	if(ensure(InGameData))
	{
		GameData = InGameData;
		if (!IsInitialized)
		{
			PlayerData = GameData->DefaultStartingData;
			PlayerData.ArmyData.GolemTypesInArmy.Empty();
		}
		OnDataInitialized.Broadcast(PlayerData);
		IsInitialized = true;
	}
}

TArray<UPDA_Golem*> UGC_PlayerDataSubsystem::GetAvailableGolemsFromGameData()
{
	TArray<UPDA_Golem*> returnValue = {};
	if (ensure(GameData))
	{
		TArray<FGolemBaseData*> GolemBaseDatas;
		GameData->AvailableGolemTypes->GetAllRows(FString("AllRows"), GolemBaseDatas);
		for (auto golemBaseData : GolemBaseDatas)
		{
			if (!golemBaseData->IsAvailable)
			{
				UE_LOG(LogTemp, Warning, TEXT("Golem not available"));
				continue;
			}
			returnValue.Add(golemBaseData->GolemData);
		}
	}
	return returnValue;
}

TArray<UPDA_Golem*> UGC_PlayerDataSubsystem::GetAvailableGolemsFromPlayerData()
{
	TArray<UPDA_Golem*> returnValue = {};
	if(ensure(GameData))
	{
		for(auto tag : PlayerData.ArmyData.TagsUnlocked)
		{
			auto golemData = GameData->AvailableGolemTypes->FindRow<FGolemBaseData>(tag.GetTagName(), "Context");
			if (!golemData->IsAvailable)
			{
				UE_LOG(LogTemp, Warning, TEXT("Golem not available"));
				continue;
			}
			returnValue.Add(golemData->GolemData);
		}
	}
	return returnValue;
}
TArray<UPDA_Golem*> UGC_PlayerDataSubsystem::GetChosenGolemsFromPlayerArmy() 
{
	return PlayerData.ArmyData.GolemTypesInArmy;
}

bool UGC_PlayerDataSubsystem::IsGolemInPlayerArmy(UPDA_Golem* DAGolem)
{
	if (ensure(DAGolem)) 
	{
		if (PlayerData.ArmyData.GolemTypesInArmy.Contains(DAGolem))
			return true;
	}
	return false;
}

bool UGC_PlayerDataSubsystem::TryAddGolemInArmy(UPDA_Golem* GolemData)
{
	if (ensure(!GolemData))
		return false;

	if (PlayerData.ArmyData.GolemTypesInArmy.Num() >= PlayerData.ArmyData.NbAvailableSlots)
		return false;

	if (PlayerData.ArmyData.TagsUnlocked.HasAllExact(GolemData->RequirementsTags))
	{
		if (ensure(GameData))
		{
			auto golemRow = GameData->AvailableGolemTypes->FindRow<FGolemBaseData>(GolemData->GolemTypeTag.GetTagName(), "Context");
			if(!golemRow)
				return false;

			if (!golemRow->IsAvailable)
			{
				UE_LOG(LogTemp, Warning, TEXT("Golem not available"));
				return false;
			}

		}
	}
	PlayerData.ArmyData.GolemTagsInArmy.AddTag(GolemData->GolemTypeTag);
	PlayerData.ArmyData.GolemTypesInArmy.Add(GolemData);
	OnArmyUpdated.Broadcast(GolemData, true, PlayerData.ArmyData);
	return true;
}

bool UGC_PlayerDataSubsystem::RemoveGolemFromArmy(UPDA_Golem* GolemData)
{
	if(PlayerData.ArmyData.GolemTypesInArmy.Remove(GolemData))
	{
		PlayerData.ArmyData.GolemTagsInArmy.RemoveTag(GolemData->GolemTypeTag);
		OnArmyUpdated.Broadcast(GolemData, false, PlayerData.ArmyData);
		return true;
	}else
	{
		return false;
	}
}

void UGC_PlayerDataSubsystem::AddToResource(FGameplayTag ResourceTag, int Value)
{
	FResourceData* resourceData = PlayerData.ResourcesData.Find(ResourceTag);
	resourceData->Quantity = FMath::Clamp(resourceData->Quantity + Value, 0, resourceData->PDA_Resource->Max);
	OnResourceUpdated.Broadcast(ResourceTag, resourceData->Quantity, Value);
}

bool UGC_PlayerDataSubsystem::PayResource(FGameplayTag ResourceTag, int Value)
{
	FResourceData* resourceData = PlayerData.ResourcesData.Find(ResourceTag);
	if (resourceData->Quantity - Value < 0)
		return false;

	resourceData->Quantity -= Value;
	OnResourceUpdated.Broadcast(ResourceTag, resourceData->Quantity, Value);
	return true;
}