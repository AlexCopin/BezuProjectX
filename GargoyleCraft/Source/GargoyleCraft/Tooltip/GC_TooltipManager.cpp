#include "GC_TooltipManager.h"

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
