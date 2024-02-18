#pragma once
struct FHeroData;
struct FArmyData;

USTRUCT(BlueprintType, Blueprintable)
struct FPlayerData
{
public:

  GENERATED_BODY()
public:
  FHeroData HeroData;
  FArmyData ArmyData;
};

USTRUCT(BlueprintType, Blueprintable)
struct FHeroData
{
public:

  GENERATED_BODY()
public:
};

USTRUCT(BlueprintType, Blueprintable)
struct FArmyData
{
public:

  GENERATED_BODY()
public:
};
