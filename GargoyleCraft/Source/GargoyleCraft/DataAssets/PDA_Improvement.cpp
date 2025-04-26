#include "PDA_Improvement.h"
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayAbilities/GC_GameplayAbility.h"


void UPDA_Improvement::ApplyImprovement(UGC_AbilitySystemComponent* ASC)
{
    for(auto ability : Abilities)
    {
      FGameplayAbilitySpec spec(ability);
      ASC->GiveAbility(spec);
    }
    for(auto effect : GameplayEffects)
    {
      FGameplayEffectSpecHandle spec = ASC->MakeOutgoingSpec(effect, 1, ASC->MakeEffectContext());
      ASC->ApplyGameplayEffectSpecToSelf(*spec.Data);
    }
}

FTooltipData UPDA_Improvement::GetTooltip_Implementation(UObject* WorldContext)
{
	FTooltipData tooltipData;
	FString AddedString;
	for (auto effect : GameplayEffects)
	{
		const UGameplayEffect* DefaultEffect = effect->GetDefaultObject<UGameplayEffect>();
		if (!DefaultEffect)
			continue;
		for (auto mod : DefaultEffect->Modifiers)
		{
			AddedString += "\n" + UGC_TooltipLibrary::ConstructGameplayEffectModifierInfos(mod);
		}
	}
	tooltipData.Description = FText::FromString(AddedString);
	return tooltipData;
}
