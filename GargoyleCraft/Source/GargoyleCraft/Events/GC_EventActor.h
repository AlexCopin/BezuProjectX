#pragma once

#include "CoreMinimal.h"
#include <GargoyleCraft/Widgets/GC_Widget.h>
#include "GargoyleCraft/Interfaces/Initializable.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GC_EventActor.generated.h"

UCLASS()
class AGC_EventActor : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	FTimerHandle TimerCustomTick;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	bool bActivateCustomTick = true;
	UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (EditCondition = "bActivateCustomTick"))
	float CustomTickDelay = 0.2f;

	UFUNCTION(BlueprintNativeEvent)
	void CustomTick();
	virtual void CustomTick_Implementation();

	void ActivateCustomTick(bool Activate);

	FMonsterEventData EventData;

	FTimerHandle SpawnTimer;
	UFUNCTION()
	void SpawnActor();
	FTimerHandle EventDuration;
	UFUNCTION()
	void EndEvent();

	int CurrentSpawnData = 0;
	UPROPERTY()
	TArray<FSpawnData> SpawnDatas;
public:

	void Init(const FMonsterEventData& Data);

	virtual void BeginPlay() override;

};