#pragma once

#include "GargoyleCraft/Golems/Data/PDA_Golem.h"
#include "GargoyleCraft/Golems/Data/PDA_GolemArmy.h"
#include "GC_Structs.generated.h"

class UGC_GameplayAbility;
class UPDA_GameplayAbility;

USTRUCT(BlueprintType, Blueprintable)
struct FHeroData
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UPDA_Golem> PDA_Hero;
};

USTRUCT(BlueprintType, Blueprintable)
struct FArmyData
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flavor)
    FText Name;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true), Category = Flavor)
    FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int NbAvailableSlots = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	FGameplayTagContainer TagsUnlocked;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    TArray<TObjectPtr<UPDA_Golem>> GolemTypesInArmy;
};

USTRUCT(BlueprintType, Blueprintable)
struct FPlayerData
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FHeroData HeroData;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FArmyData ArmyData;
};


USTRUCT(BlueprintType, Blueprintable)
struct FAbilityData
{
	GENERATED_BODY()
	FGameplayAbilitySpecHandle AbilityHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
};

USTRUCT(BlueprintType, Blueprintable)
struct FTooltipData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Flavor;

};
