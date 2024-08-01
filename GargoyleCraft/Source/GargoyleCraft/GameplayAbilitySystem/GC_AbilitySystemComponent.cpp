#include "GC_AbilitySystemComponent.h"

#include "AttributeSets/AttributeSet_Character.h"

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