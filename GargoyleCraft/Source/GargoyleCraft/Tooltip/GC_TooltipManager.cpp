#include "GC_TooltipManager.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"

FString UGC_TooltipLibrary::ConstructGameplayEffectModifierInfos(const FGameplayModifierInfo& ModInfos)
{
	FString returnString;
	returnString += ModInfos.Attribute.GetName();
	float magnitude = 0;
	if(ModInfos.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, magnitude))
	{
		if (ModInfos.ModifierOp == EGameplayModOp::AddBase || ModInfos.ModifierOp == EGameplayModOp::AddFinal || ModInfos.ModifierOp == EGameplayModOp::Additive)
		{
			FString magnString = (1 - magnitude > 0) ? "+" : "";
			returnString += magnString + FString::FromInt(magnitude);
		}
		else if (ModInfos.ModifierOp == EGameplayModOp::Multiplicitive || ModInfos.ModifierOp == EGameplayModOp::MultiplyAdditive || ModInfos.ModifierOp == EGameplayModOp::Division)
		{
			FString magnString = (1 - magnitude > 0) ? "+" : "";
			returnString += magnString + FString::FromInt((1 - magnitude) * 100) + "%";
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
	WorldContext->GetWorld();
	for(auto attribute : attributesOut)
	{
		bool bIsFound;
		ASC->GetGameplayAttributeValue(attribute, bIsFound);
		attribute.GetNumericValue(attributeSet);
	}
	return tooltipData;
}
