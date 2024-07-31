#pragma once

#include "GC_PC_RTS.generated.h"

class AGolem;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGolemSelection, AGolem*, Golem);

UCLASS()
class GARGOYLECRAFT_API AGC_PC_RTS : public APlayerController
{
  GENERATED_BODY()
public:
  UPROPERTY(BlueprintAssignable)
  FOnGolemSelection OnGolemAdded;
  UPROPERTY(BlueprintAssignable)
  FOnGolemSelection OnGolemRemoved;
  UFUNCTION(BlueprintCallable)
  bool AddToSelectedGolems(AGolem* Golem);
  UFUNCTION(BlueprintCallable)
  void RemoveFromSelectedGolems(AGolem* Golem);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AGolem*> SelectedGolems;
};