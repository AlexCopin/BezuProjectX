#include "PDA_DefaultActorData.h"

#include "AbilitySystemInterface.h"
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"

void UPDA_DefaultActorData::Apply(UAbilitySystemComponent* ASC)
{
    if(ASC)
    {
		for(auto ability : StartingAbilities)
		{
			auto spec = FGameplayAbilitySpec(ability, 1, INDEX_NONE, this);
			ASC->GiveAbility(spec);
		}
    }
}
