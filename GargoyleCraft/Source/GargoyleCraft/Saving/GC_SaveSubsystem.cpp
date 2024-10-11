#include "GC_SaveSubsystem.h"

#include "Engine/DataTable.h"

#include "GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h"

bool UGC_SaveSubsystem::SavePlayerData()
{
	FPlayerData currentData = GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->PlayerData;
	TArray<FString> SavedPlayerData;
	/*auto currentClass = currentData.ArmyData.StaticStruct()->GetClass();
	if(ensure(currentClass))
	{
		auto currentProp = currentClass->PropertyLink;
		while (currentProp)
		{
			FString propName = currentProp->GetNameCPP();
			FString value;
			currentProp->ExportTextItem_Direct(value, currentProp, nullptr, currentClass, 0);
			UE_LOG(LogTemp, Warning, TEXT("Struct prop == %s -- Value == %s"), *propName, *value);
			SavedPlayerData.Add(propName + "-" + value);
			currentProp = currentProp->PropertyLinkNext->IsValidLowLevel() ? currentProp->PropertyLinkNext : nullptr;
		}
		return FFileHelper::SaveStringArrayToFile(SavedPlayerData, *FILE_NAME);
	}*/

	FString nbSlots = FString::FromInt(currentData.ArmyData.NbAvailableSlots);
	//FString nbSlots = FString("NbSlots-" + FString::FromInt(currentData.ArmyData.NbAvailableSlots));
	SavedPlayerData.Add(nbSlots);

	FString tagsUnlocked = currentData.ArmyData.TagsUnlocked.ToString();
	//FString tagsUnlocked = FString("TagsUnlocked-" + currentData.ArmyData.TagsUnlocked.ToString());
	SavedPlayerData.Add(tagsUnlocked);

	FString description = currentData.ArmyData.Description.ToString();
	//FString description = FString("Description-" + currentData.ArmyData.Description.ToString());
	SavedPlayerData.Add(description);

	return FFileHelper::SaveStringArrayToFile(SavedPlayerData, *FILE_NAME);
}

FPlayerData UGC_SaveSubsystem::LoadPlayerData()
{
	TArray<FString> SaveArray;
	if(FFileHelper::LoadFileToStringArray(SaveArray, *FILE_NAME))
	{
		FPlayerData currentData = GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->PlayerData;
		SaveArray[0];
	}

	return FPlayerData();
}
