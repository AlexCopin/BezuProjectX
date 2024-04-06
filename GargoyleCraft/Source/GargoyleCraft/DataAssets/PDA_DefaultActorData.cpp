#include "PDA_DefaultActorData.h"

#include "AbilitySystemInterface.h"
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"

void UPDA_DefaultActorData::Apply(AActor* Actor)
{
	/*auto asc = Cast<IAbilitySystemInterface>(Actor)->GetAbilitySystemComponent();
    if(asc)
    {
		asc->DefaultStartingData.Append(DefaultStartingData);
	    if(auto gcAsc = Cast<UGC_AbilitySystemComponent>(asc))
	    {
			gcAsc->ApplyDefaultValues();
	    }
    }*/
}
