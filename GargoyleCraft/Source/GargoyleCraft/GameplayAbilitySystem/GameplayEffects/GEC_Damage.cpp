// Fill out your copyright notice in the Description page of Project Settings.


#include "GEC_Damage.h"

#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"

void UGEC_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                         FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	//ADD MODIFIERS FOR DAMAGE (REDUCTION ETC..)

	FGameplayEffectAttributeCaptureDefinition captDef;
	captDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	captDef.AttributeToCapture = UAttributeSet_Character::GetMetaDamageAttribute();
	FAggregatorEvaluateParameters evalParams;
	float outMetaDamageValue = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(captDef, FAggregatorEvaluateParameters(), outMetaDamageValue);

	//Straight forward damage dealing without other modifiers
	{
		FGameplayModifierEvaluatedData outputModifier;
		outputModifier.Attribute = UAttributeSet_Character::GetHPAttribute();
		outputModifier.ModifierOp = EGameplayModOp::Additive;
		outputModifier.Magnitude = -1 * outMetaDamageValue;
		OutExecutionOutput.AddOutputModifier(outputModifier);
	}
	//Reset MetaDamage Attribute
	{
		FGameplayModifierEvaluatedData outputModifier;
		outputModifier.Attribute = UAttributeSet_Character::GetMetaDamageAttribute();
		outputModifier.ModifierOp = EGameplayModOp::Override;
		outputModifier.Magnitude = 0;
		OutExecutionOutput.AddOutputModifier(outputModifier);
	}
}
