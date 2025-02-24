#pragma once

#include "GargoyleCraft/Golems/Data/PDA_Golem.h"
#include "GargoyleCraft/Golems/Data/PDA_GolemArmy.h"
#include <GargoyleCraft/Craft/PDA_Blueprint.h>
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Craft")
	FGameplayTagContainer RecipeTagsUnlocked;
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
struct FRecipeData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag RecipeTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPDA_Blueprint> RecipeData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsAvailable;
};

USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<AActor> SpawnedActor;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	float Delay = 2.0f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	TObjectPtr<AActor> SpawnPoint;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	FVector SpawnPosition;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	int Number = 1;
};


USTRUCT(BlueprintType)
struct FMonsterEventData
{
	GENERATED_BODY()
public:
	//Can be overriden
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	float Duration;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	float SpawnOffsetMax = 1.0f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	int TotalNumberToSpawn;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	FVector2D NumberRange;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	FVector2D SpawnRange = FVector2D(400.0, 600.0);
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")
	TArray<TSubclassOf<AGolem>> SpawnedActors;
};


USTRUCT(BlueprintType)
struct FLootData
{
	GENERATED_BODY()
public:
	//Can be tag of Recipes / Resources
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FGameplayTag LootTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	int Num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1), Category="Settings")
	float DropChance;
};