// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GargoyleCraft/Actors/GC_Actor.h"
#include "GC_LeaveLevel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGolemDetected, bool, isDetected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelDepartureStarted, float, Duration);

UCLASS()
class GARGOYLECRAFT_API AGC_LeaveLevel : public AGC_Actor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGC_LeaveLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void GoToLevel();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartLevelDeparture();
	void StartLevelDeparture_Implementation();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWorld> LevelToGoTo;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGC_Widget> ActorWidget;


	UPROPERTY(EditAnywhere, Category = "Settings")
	float RangeScan;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float LeaveDuration = 5.f;
	UPROPERTY()
	FTimerHandle TimerBeforeDeparture;

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FGolemDetected OnGolemDetected;
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FLevelDepartureStarted OnLevelDepartureStarted;

	virtual void CustomTick_Implementation() override;
	//Initializable
	virtual void Initialize_Implementation(FPlayerData DataSent) override;
};
