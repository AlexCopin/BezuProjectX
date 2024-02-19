#pragma once

#include "GargoyleCraft/Golems/Data/PDA_Golem.h"
#include "GargoyleCraft/Golems/Data/PDA_GolemArmy.h"
#include "GC_Structs.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FHeroData
{
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UPDA_Golem> HeroPDA;
};

USTRUCT(BlueprintType, Blueprintable)
struct FArmyData
{
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UPDA_GolemArmy> ArmyPDA;
};

USTRUCT(BlueprintType, Blueprintable)
struct FPlayerData
{
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FHeroData HeroData;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FArmyData ArmyData;
};
