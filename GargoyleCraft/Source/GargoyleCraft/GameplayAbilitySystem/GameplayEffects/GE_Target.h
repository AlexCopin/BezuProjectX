#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_Target.generated.h"

/**
 *
 */
UCLASS()
class GARGOYLECRAFT_API UGE_Target : public UGameplayEffect
{
	GENERATED_BODY()
	UGE_Target();
	virtual void PostInitProperties() override;
};
