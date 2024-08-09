// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_MoveForced.h"
#include "GameplayAbilities/Public/GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GargoyleCraft/Include/GC_Macros.h"

UGE_MoveForced::UGE_MoveForced()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
}

void UGE_MoveForced::PostInitProperties()
{
	Super::PostInitProperties();
	FInheritedTagContainer TagContainer = FInheritedTagContainer();
	UTargetTagsGameplayEffectComponent& Component = FindOrAddComponent<UTargetTagsGameplayEffectComponent>();
	TagContainer.Added.AddTag(MAKE_TAG("State.Moving.Forced"));
	Component.SetAndApplyTargetTagChanges(TagContainer);
}
