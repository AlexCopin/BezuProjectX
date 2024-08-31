#include "GE_ActivateAbility.h"
#include "GameplayAbilities/Public/GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GargoyleCraft/Include/GC_Macros.h"

UGE_ActivateAbility::UGE_ActivateAbility()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
}

void UGE_ActivateAbility::PostInitProperties()
{
	Super::PostInitProperties();
	FInheritedTagContainer TagContainer = FInheritedTagContainer();
	UTargetTagsGameplayEffectComponent& Component = FindOrAddComponent<UTargetTagsGameplayEffectComponent>();
	TagContainer.Added.AddTag(MAKE_TAG("State.Ability.Ongoing"));
	Component.SetAndApplyTargetTagChanges(TagContainer);
}
