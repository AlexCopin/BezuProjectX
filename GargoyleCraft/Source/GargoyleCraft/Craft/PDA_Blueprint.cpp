#include "PDA_Blueprint.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>

#define LOCTEXT_NAMESPACE "Recipe"
FTooltipData UPDA_Blueprint::GetTooltip_Implementation(UObject* WorldContext)
{
	// Append with a space between
	FTooltipData tempData = Super::GetTooltip_Implementation(WorldContext);
	TArray<FGameplayTag> keys;
	ResourcesRequired.GetKeys(keys);
	FString resourcesInfos;
	auto playerDataSS = WorldContext->GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>();
	for(FGameplayTag resourceTag : keys)
	{
		resourcesInfos += playerDataSS->GetSimpleTooltip(resourceTag).Title.ToString() + " x" + FString::FromInt(*ResourcesRequired.Find(resourceTag)) + "\n";
	}
	tempData.Description = FText::Format(LOCTEXT("Recipe.Tooltip", "{OriginalDesc}\nChanges : {ImprovementDesc}\nCost : {ResourcesRequired}"), TooltipData.Description, Execute_GetTooltip(Improvement, WorldContext).Description, FText::FromString(resourcesInfos));
	return tempData;
}

#undef LOCTEXT_NAMESPACE