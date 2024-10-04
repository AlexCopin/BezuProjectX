// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_PlayerDataSubsystem.h"

#include "GargoyleCraft/GameData/PDA_GameData.h"

void UGC_PlayerDataSubsystem::SetGameData(UPDA_GameData* InGameData)
{
	//if no saves
	if(ensure(InGameData))
	{
		GameData = InGameData;
		PlayerData = GameData->DefaultStartingData;
		OnDataInitialized.Broadcast(PlayerData);
	}
}

TArray<UPDA_Golem*> UGC_PlayerDataSubsystem::GetAvailableGolemsFromPlayerData()
{

	TArray<UPDA_Golem*> returnValue = {};
	if(ensure(GameData))
	{
		for (auto golemType : GameData->AvailableGolemTypes)
		{
			if (PlayerData.ArmyData.TagsUnlocked.HasAllExact(golemType->RequirementsTags))
				returnValue.Add(golemType);
		}
	}
	return returnValue;
}

bool UGC_PlayerDataSubsystem::TryAddGolemInArmy(UPDA_Golem* GolemData)
{
	if (PlayerData.ArmyData.GolemTypesInArmy.Num() >= PlayerData.ArmyData.NbAvailableSlots)
		return false;

	PlayerData.ArmyData.GolemTypesInArmy.Add(GolemData);
	return true;
}

bool UGC_PlayerDataSubsystem::RemoveGolemFromArmy(UPDA_Golem* GolemData)
{
	if(PlayerData.ArmyData.GolemTypesInArmy.Remove(GolemData))
	{
		return true;
	}else
	{
		return false;
	}
}
