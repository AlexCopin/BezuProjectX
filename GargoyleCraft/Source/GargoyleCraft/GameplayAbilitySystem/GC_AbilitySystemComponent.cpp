#include "GC_AbilitySystemComponent.h"

#include "AttributeSets/AttributeSet_Character.h"
#include "Data/PDA_GameplayAbility.h"
#include "GameplayAbilities/GC_GameplayAbility.h"
#include "GargoyleCraft/Include/GC_Structs.h"

void UGC_AbilitySystemComponent::Init()
{
}

void UGC_AbilitySystemComponent::ApplyDefaultValues()
{	
  for (int32 i = 0; i < DefaultStartingData.Num(); ++i)
  {
    if (DefaultStartingData[i].Attributes && DefaultStartingData[i].DefaultStartingTable)
    {
      UAttributeSet* Attributes = const_cast<UAttributeSet*>(GetOrCreateAttributeSubobject(DefaultStartingData[i].Attributes));
      Attributes->InitFromMetaDataTable(DefaultStartingData[i].DefaultStartingTable);
    }
  }
}

void UGC_AbilitySystemComponent::AddGameplayAbility(UPDA_GameplayAbility* AbilityData)
{
	auto spec = FGameplayAbilitySpec(AbilityData->AbilityClass, 1, INDEX_NONE, GetOwner());
	FAbilityData abilityData = AbilityData->AbilityData;
	abilityData.AbilityHandle = GiveAbility(spec);
	AbilitiesData.Emplace(abilityData.AbilityHandle, AbilityData);
	Abilities.Add(abilityData);
}

UPDA_GameplayAbility* UGC_AbilitySystemComponent::GetAbilityDataFromSpecHandle(FGameplayAbilitySpecHandle Handle)
{
	return AbilitiesData[Handle];
}
