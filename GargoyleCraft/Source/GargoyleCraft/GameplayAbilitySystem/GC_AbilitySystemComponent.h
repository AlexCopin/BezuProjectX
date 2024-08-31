#pragma once
#include "AbilitySystemComponent.h"

#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GC_AbilitySystemComponent.generated.h"

struct FAbilityData;
class UPDA_GameplayAbility;

UCLASS()
class GARGOYLECRAFT_API UGC_AbilitySystemComponent : public UAbilitySystemComponent
{
  GENERATED_BODY()
public:
  void Init();
  UFUNCTION()
  void ApplyDefaultValues();
	UFUNCTION(BlueprintCallable)
	void AddGameplayAbility(UPDA_GameplayAbility* AbilityData);

	UFUNCTION()
	UPDA_GameplayAbility* GetAbilityDataFromSpecHandle(FGameplayAbilitySpecHandle Handle);
	TMap<FGameplayAbilitySpecHandle, UPDA_GameplayAbility*> AbilitiesData;
	TArray<FAbilityData> Abilities;
};