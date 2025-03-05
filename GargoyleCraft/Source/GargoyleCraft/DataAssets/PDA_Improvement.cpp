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

FTooltipData UPDA_Improvement::GetTooltip_Implementation()
{
	FTooltipData tooltipData;
	FString AddedString;
	int i = 0;
	for (auto effect : GameplayEffects)
	{
		i++;
		AddedString += "\n" + FString::FromInt(i);
		const UGameplayEffect* DefaultEffect = effect->GetDefaultObject<UGameplayEffect>();
		if (!DefaultEffect)
			continue;
		for (auto mod : DefaultEffect->Modifiers)
		{
			AddedString += "\n- " + UGC_TooltipLibrary::ConstructGameplayEffectModifierInfos(mod) + "\n";
		}
	}
	tooltipData.Description = FText::FromString(AddedString);
	return tooltipData;
}
