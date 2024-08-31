// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_Damage.h"

#include "GEC_Damage.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"
#include "GargoyleCraft/Include/GC_Macros.h"

UGE_Damage::UGE_Damage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
}

void UGE_Damage::PostInitProperties()
{
	Super::PostInitProperties();
	{
		FGameplayModifierInfo modifier;
		modifier.Attribute = UAttributeSet_Character::GetMetaDamageAttribute();
		FSetByCallerFloat setByCaller;
		setByCaller.DataTag = MAKE_TAG("MetaDamage.Value");
		const FGameplayEffectModifierMagnitude modMagnitude(setByCaller);
		modifier.ModifierMagnitude = modMagnitude;
		modifier.ModifierOp = EGameplayModOp::Override;

		Modifiers.Add(modifier);
	}

	FGameplayEffectExecutionDefinition execDef(UGEC_Damage::StaticClass());
	Executions.Add(execDef);
}
