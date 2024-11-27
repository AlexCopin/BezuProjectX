#pragma once

#include "GargoyleCraft/Golems/Data/PDA_Golem.h"
#include "GargoyleCraft/Golems/Data/PDA_GolemArmy.h"
#include "GC_Structs.generated.h"

class UGC_GameplayAbility;
class UPDA_GameplayAbility;
class UPDA_Resource;

USTRUCT(BlueprintType, Blueprintable)
struct FResourceData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Quantity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPDA_Resource> PDA_Resource;
};
USTRUCT(BlueprintType, Blueprintable)
struct FHeroData
{
  GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UPDA_Golem> PDA_Hero;
};

USTRUCT(BlueprintType, Blueprintable)
struct FArmyData
{
  GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flavor)
    FText Name;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true), Category = Flavor)
    FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int NbAvailableSlots = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	FGameplayTagContainer TagsUnlocked;
	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer GolemTagsInArmy;
    UPROPERTY(BlueprintReadOnly)
    TArray<TObjectPtr<UPDA_Golem>> GolemTypesInArmy;
};


USTRUCT(BlueprintType, Blueprintable)
struct FPlayerData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	FHeroData HeroData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	FArmyData ArmyData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	TMap<FGameplayTag, FResourceData> ResourcesData;
};

USTRUCT(BlueprintType, Blueprintable)
struct FAbilityData
{
	GENERATED_BODY()
public:
	FGameplayAbilitySpecHandle AbilityHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag CooldownTag;
};


USTRUCT(BlueprintType)
struct FGolemBaseData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag GolemTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPDA_Golem> GolemData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsAvailable;
};

USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SpawnSettings")
	TSubclassOf<AActor> SpawnedActor;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SpawnSettings")
	float Delay = 2.0f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SpawnSettings")
	TObjectPtr<AActor> SpawnPoint;
};