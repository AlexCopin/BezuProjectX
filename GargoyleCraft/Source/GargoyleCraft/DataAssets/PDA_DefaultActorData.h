#pragma once

#include "PDA_DefaultActorData.generated.h"


class UGameplayAbility;
class UAbilitySystemComponent;
class UGC_GameplayAbility_Character;
struct FAttributeDefaults;

UCLASS()
class GARGOYLECRAFT_API UPDA_DefaultActorData : public UPrimaryDataAsset
{
  GENERATED_BODY()
public:
  virtual void Apply(UAbilitySystemComponent* ASC);
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
  UPROPERTY(EditDefaultsOnly, Category = Gameplay)
  TArray<FAttributeDefaults> DefaultStartingData;
};