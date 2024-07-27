#pragma once
#include "GargoyleCraft/Include/GC_GolemTypes.h"

#include "C_Pool.generated.h"

UCLASS()
class UC_Pool : public UActorComponent
{
  GENERATED_BODY()
public:
  
  virtual void BeginPlay() override;

  UPROPERTY(BlueprintReadWrite, EditAnywhere)
  TEnumAsByte<EGolemAllegiance> GolemAllegiance;
  UPROPERTY(BlueprintReadWrite, EditAnywhere)
  TArray<TEnumAsByte<EGolemAllegiance>> HostileDiplomacies;

protected:
  UFUNCTION()
  void AddToPool();
  UFUNCTION()
  void RemoveFromPool();
};