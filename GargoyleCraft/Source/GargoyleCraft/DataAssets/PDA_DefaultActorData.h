#pragma once

#include "PDA_DefaultActorData.generated.h"


struct FAttributeDefaults;

UCLASS()
class GARGOYLECRAFT_API UPDA_DefaultActorData : public UPrimaryDataAsset
{
  GENERATED_BODY()
public:
  virtual void Apply(AActor* Actor);
  UPROPERTY(EditDefaultsOnly, Category = Gameplay)
  TArray<FAttributeDefaults> DefaultStartingData;
};