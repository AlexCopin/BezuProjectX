#pragma once
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

#include "AttributeSet_Character.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GARGOYLECRAFT_API UAttributeSet_Character : public UAttributeSet
{
  GENERATED_BODY()
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MetaDamage;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Character, MetaDamage);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Character, HP);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Character, MaxHP);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData RegenHP;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Character, RegenHP);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Character, MovementSpeed);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FGameplayAttributeData AggroRange;
  ATTRIBUTE_ACCESSORS(UAttributeSet_Character, AggroRange);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FGameplayAttributeData AttackRange;
  ATTRIBUTE_ACCESSORS(UAttributeSet_Character, AttackRange);


};