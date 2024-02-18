#pragma once
#include "GC_Structs.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FHeroData
{
  GENERATED_BODY()
public:
};

USTRUCT(BlueprintType, Blueprintable)
struct FArmyData
{
  GENERATED_BODY()
public:
};

USTRUCT(BlueprintType, Blueprintable)
struct FPlayerData
{
  GENERATED_BODY()
public:
  FHeroData HeroData;
  FArmyData ArmyData;
};
