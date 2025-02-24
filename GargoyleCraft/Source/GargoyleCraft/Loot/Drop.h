// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GargoyleCraft/Actors/GC_Actor.h"
#include "GargoyleCraft/Include/GC_Structs.h"

#include "Drop.generated.h"

UCLASS()
class GARGOYLECRAFT_API ADrop : public AGC_Actor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintNativeEvent)
	void ConsumeDrop();
	void ConsumeDrop_Implementation();

	UPROPERTY(BlueprintReadOnly)
	FLootData _LootData;

public:
	// Sets default values for this actor's properties
	ADrop();
	UPROPERTY(EditAnywhere, Category = "Settings")
	float RangeScan;

	void Init(const FLootData& LootData);

	virtual void CustomTick_Implementation() override;
	//Initializable
	virtual void Initialize_Implementation(FPlayerData DataSent) override;

private:

	
	bool bIsConsumed = false;
};
