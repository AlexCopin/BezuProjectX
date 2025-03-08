#include "PDA_Blueprint.h"

FTooltipData UPDA_Blueprint::GetTooltip_Implementation()
{
	// Append with a space between
	FTooltipData tempData = Super::GetTooltip_Implementation();
	TArray<FGameplayTag> keys;
	ResourcesRequired.GetKeys(keys);
	FString resourcesInfos;
	for(FGameplayTag resourceTag : keys)
	{
		resourcesInfos += resourceTag.GetTagName().ToString() + " - " + FString::FromInt(*ResourcesRequired.Find(resourceTag)) + "\n";
	}
	FFormatNamedArguments Args;
	Args.Add(TEXT("OriginalDesc"), TooltipData.Description);
	Args.Add(TEXT("ResourcesRequired"), FText::FromString(resourcesInfos));
	Args.Add(TEXT("ImprovementDesc"), Improvement->GetTooltip().Description);
	tempData.Description = FText::Format(FText::FromString("{OriginalDesc}\n*Changes : {ImprovementDesc} \n*Cost : {ResourcesRequired}"), Args);
	return tempData;
}
