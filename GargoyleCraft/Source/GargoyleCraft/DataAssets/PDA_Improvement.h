#pragma once

#include "PDA_Improvement.generated.h"

class UGameplayEffect;
class UGC_AbilitySystemComponent;
struct FAttributeDefaults;
class UGC_GameplayAbility;

UCLASS()
class GARGOYLECRAFT_API UPDA_Improvement : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

  void ApplyImprovement(UGC_AbilitySystemComponent* ASC);

    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
    TArray<TSubclassOf<UGC_GameplayAbility>> Abilities;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;
};