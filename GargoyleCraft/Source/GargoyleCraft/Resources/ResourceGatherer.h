#pragma once

#include "GargoyleCraft/Golems/Interfaces/Selectable.h"
#include "GargoyleCraft/Actors/GC_Actor.h"
#include <GargoyleCraft/Widgets/GC_Widget.h>
#include "GameplayTagContainer.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "ResourceGatherer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGolemScanned, bool, isScanned);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConstructionStarted, float, Duration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGatheringStarted, float, Duration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGathered, int, Value);

UCLASS()
class AResourceGatherer : public AGC_Actor, public ISelectable
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
	float DelayBetweenGathering;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
	int Uses = 20;
	int Counter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
	int QuantityResource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
	FGameplayTag ResourceTag;

	UPROPERTY()
	FTimerHandle TimerGathering;
	UPROPERTY()
	FTimerHandle TimerConstruction;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float RangeScan;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gathering")
	float ConstructionDuration;

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FConstructionStarted OnConstructionStarted;
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FGatheringStarted OnGatheringStarted;
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FGathered OnGathered;
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FGolemScanned OnGolemScanned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FMonsterEventData EventData;

	UFUNCTION(BlueprintCallable)
	void BeginConstruct();
	UFUNCTION()
	void FinishConstruct();
	UFUNCTION(BlueprintNativeEvent)
	void Gather();
	void Gather_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void Terminate();
	void Terminate_Implementation();

	virtual void CustomTick_Implementation() override;
};