#pragma once

#include "GC_PC_RTS.generated.h"

class AGolem;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGolemSelection, AGolem*, Golem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetsUpdated, AGC_PC_RTS*, PlayerController);

UCLASS()
class GARGOYLECRAFT_API AGC_PC_RTS : public APlayerController
{
  GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnTargetsUpdated OnTargetsUpdated;
  UPROPERTY(BlueprintAssignable)
  FOnGolemSelection OnGolemAdded;
  UPROPERTY(BlueprintAssignable)
  FOnGolemSelection OnGolemRemoved;
  UFUNCTION(BlueprintCallable)
  void AddToSelectedGolems(AGolem* Golem);
  UFUNCTION(BlueprintCallable)
  void RemoveFromSelectedGolems(AGolem* Golem);
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
  void TryToSelectGolemArray(const TArray<AActor*>& Golems, bool bAdditive);
  UFUNCTION()
  void SelectGolemArray(TArray<AActor*> Golems, bool bAdditive);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AGolem*> SelectedGolems;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AGolem*> ControlableGolems;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool TryMoveGolemsToLocation(FVector Location);
	bool TryMoveGolemsToLocation_Implementation(FVector Location);

};