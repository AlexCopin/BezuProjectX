#pragma once

#include "CoreMinimal.h"
#include "GargoyleCraft/Golems/Interfaces/Selectable.h"
#include <GargoyleCraft/Widgets/GC_Widget.h>
#include "GameplayTagContainer.h"
#include "ResourceGatherer.generated.h"

UCLASS()
class AResourceGatherer : public AActor, public ISelectable
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gathering")
	TSubclassOf<UGC_Widget> WidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gathering")
	float ConstructionDuration;

	UFUNCTION(BlueprintCallable)
	void BeginConstruct();
	UFUNCTION()
	void FinishConstruct();
	UFUNCTION()
	void Gather();
	UFUNCTION(BlueprintNativeEvent)
	void Terminate();
	void Terminate_Implementation();
};