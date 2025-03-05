#include "PDA_Blueprint.h"

FTooltipData UPDA_Blueprint::GetTooltip_Implementation()
{
	// Append with a space between
	FTooltipData tempData = Super::GetTooltip_Implementation();
	TArray<FGameplayTag> keys;
	ResourcesRequired.GetKeys(keys);
	FText resourcesInfos;
	for(FGameplayTag resourceTag : keys)
	{
		resourcesInfos = FText::FromString(resourceTag.GetTagName().ToString() + " - " + FString::FromInt(*ResourcesRequired.Find(resourceTag)) + "\n");
	}
	FFormatNamedArguments Args;
	Args.Add(TEXT("OriginalDesc"), TooltipData.Description);
	Args.Add(TEXT("ResourcesRequired"), resourcesInfos);
	Args.Add(TEXT("ImprovementDesc"), Improvement->GetTooltip().Description);
	tempData.Description = FText::Format(FText::FromString("{OriginalDesc} Changes : {ImprovementDesc} \n {ResourcesRequired}"), Args);
	return tempData;
}
