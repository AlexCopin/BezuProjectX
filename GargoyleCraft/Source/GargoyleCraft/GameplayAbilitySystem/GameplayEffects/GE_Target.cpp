#include "GE_Target.h"
#include "GameplayAbilities/Public/GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GargoyleCraft/Include/GC_Macros.h"

UGE_Target::UGE_Target()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
}

void UGE_Target::PostInitProperties()
{
	Super::PostInitProperties();
	UTargetTagRequirementsGameplayEffectComponent& Component = FindOrAddComponent<UTargetTagRequirementsGameplayEffectComponent>();
	Component.RemovalTagRequirements.RequireTags.AddTag(MAKE_TAG("State.Moving.Forced"));


	FInheritedTagContainer TagContainer = FInheritedTagContainer();
	UTargetTagsGameplayEffectComponent& TagsComponent = FindOrAddComponent<UTargetTagsGameplayEffectComponent>();
	TagContainer.Added.AddTag(MAKE_TAG("State.Targeting"));
	TagsComponent.SetAndApplyTargetTagChanges(TagContainer);
}
