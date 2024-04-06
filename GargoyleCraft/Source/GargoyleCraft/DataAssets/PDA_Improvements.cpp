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
