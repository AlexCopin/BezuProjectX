#pragma once

#include "CoreMinimal.h"
#include <GargoyleCraft/Widgets/GC_Widget.h>
#include "GargoyleCraft/Interfaces/Initializable.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GC_Actor.generated.h"

UCLASS()
class AGC_Actor : public AActor, public IInitializable
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

	//Initializable
	virtual void Initialize_Implementation(FPlayerData DataSent) override;
	bool Initialized = false;

public:
	virtual void BeginPlay() override;

};