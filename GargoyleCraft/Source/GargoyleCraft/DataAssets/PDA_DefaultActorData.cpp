#include "PDA_DefaultActorData.h"

#include "AbilitySystemInterface.h"
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"
#include "GargoyleCraft/GameplayAbilitySystem/Data/PDA_GameplayAbility.h"

void UPDA_DefaultActorData::Apply(UAbilitySystemComponent* ASC)
{
    if(ASC)
    {
		for(auto abilityPda : StartingAbilities)
		{
			if(ensure(abilityPda))
			{

				Cast<UGC_AbilitySystemComponent>(ASC)->AddGameplayAbility(abilityPda);
			}
		}
		auto context = ASC->MakeEffectContext();
		for(auto effect : StartingGameplayEffects)
		{
			auto effectSpec = ASC->MakeOutgoingSpec(effect, 1, context);
			ASC->ApplyGameplayEffectSpecToSelf(*effectSpec.Data);
		}
    }
}
