#pragma once
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

#include "AttributeSet_Character.generated.h"

UCLASS()
class GARGOYLECRAFT_API UAttributeSet_Character : public UAttributeSet
{
  GENERATED_BODY()
public:

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayAttributeData HP;
  GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAttributeSet_Character, HP);
  GAMEPLAYATTRIBUTE_VALUE_GETTER(HP);
  GAMEPLAYATTRIBUTE_VALUE_SETTER(HP);
  GAMEPLAYATTRIBUTE_VALUE_INITTER(HP);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayAttributeData MaxHP;
  GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAttributeSet_Character, MaxHP);
  GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHP);
  GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHP);
  GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHP);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayAttributeData MovementSpeed;
  GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAttributeSet_Character, MovementSpeed);
  GAMEPLAYATTRIBUTE_VALUE_GETTER(MovementSpeed);
  GAMEPLAYATTRIBUTE_VALUE_SETTER(MovementSpeed);
  GAMEPLAYATTRIBUTE_VALUE_INITTER(MovementSpeed);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FGameplayAttributeData AggroRange;
  GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAttributeSet_Character, AggroRange);
  GAMEPLAYATTRIBUTE_VALUE_GETTER(AggroRange);
  GAMEPLAYATTRIBUTE_VALUE_SETTER(AggroRange);
  GAMEPLAYATTRIBUTE_VALUE_INITTER(AggroRange);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FGameplayAttributeData AttackRange;
  GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAttributeSet_Character, AttackRange);
  GAMEPLAYATTRIBUTE_VALUE_GETTER(AttackRange);
  GAMEPLAYATTRIBUTE_VALUE_SETTER(AttackRange);
  GAMEPLAYATTRIBUTE_VALUE_INITTER(AttackRange);

};