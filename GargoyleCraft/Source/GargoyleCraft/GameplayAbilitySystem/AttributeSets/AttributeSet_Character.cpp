#include "AttributeSet_Character.h"

void UAttributeSet_Character::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if(Attribute == GetHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHP());
	}
}
