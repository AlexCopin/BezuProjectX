#include "GC_TooltipManager.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"
#include <GargoyleCraft/GameFramework/GC_GameModeBase.h>
#include "GargoyleCraft/GameData/PDA_GameData.h"

FString UGC_TooltipLibrary::ConstructGameplayEffectModifierInfos(const FGameplayModifierInfo& ModInfos)
{
	FString returnString;
	returnString += ModInfos.Attribute.GetName();
	float magnitude = 0;
	if(ModInfos.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, magnitude))
	{
		if (ModInfos.ModifierOp == EGameplayModOp::AddBase || ModInfos.ModifierOp == EGameplayModOp::AddFinal || ModInfos.ModifierOp == EGameplayModOp::Additive)
		{
			FString magnString = (magnitude > 0) ? "+" : "-";
			returnString += magnString + FString::FromInt(magnitude);
		}
		else if (ModInfos.ModifierOp == EGameplayModOp::Multiplicitive || ModInfos.ModifierOp == EGameplayModOp::MultiplyAdditive || ModInfos.ModifierOp == EGameplayModOp::Division)
		{
			FString magnString = (magnitude - 1 > 0) ? "+" : "-";
			returnString += magnString + FString::FromInt((magnitude - 1) * 100) + "%";
		}
	}
    return returnString;
}

FTooltipData UGC_TooltipLibrary::GetTooltipDataFromAbilitySystemComponent(UObject* WorldContext, UGC_AbilitySystemComponent* ASC)
{
	FTooltipData tooltipData;
	auto attributeSet = ASC->GetAttributeSet(UAttributeSet_Character::StaticClass());
	TArray<FGameplayAttribute> attributesOut;
	ASC->GetAllAttributes(attributesOut);
	//Finish here by getting AttributeDisplayData for each attribute and building the tooltipData
	auto gameData = WorldContext->GetWorld()->GetAuthGameMode<AGC_GameModeBase>()->DefaultGameData;
	FString stringAttributes = "Stats\n";
	for(auto attribute : attributesOut)
	{
		auto attributeDisplayData = gameData->FindAttributeDisplayValue(attribute);
		if (attributeDisplayData.IsHidden)
			continue;
		stringAttributes += attributeDisplayData.TooltipData.Title.ToString() + FString::SanitizeFloat(attribute.GetNumericValue(ASC->GetAttributeSet(UAttributeSet_Character::StaticClass()))) + "\n";
	}
	tooltipData.Title = FText::FromString(ASC->GetOwner()->GetName());
	tooltipData.Description = FText::FromString(stringAttributes);
	return tooltipData;
}
