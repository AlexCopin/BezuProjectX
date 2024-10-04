// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GargoyleCraft/Include/GC_GolemTypes.h"
#include "GC_GS_RTS.generated.h"


#define GET_GS_RTS() (GetWorld() ? GetWorld()->GetGameState<AGC_GS_RTS>() : nullptr)
class UPDA_GameData;
class AGolem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPoolUpdated, AGC_GS_RTS*, GameState);

UCLASS()
class GARGOYLECRAFT_API AGC_GS_RTS : public AGameStateBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPDA_GameData> DefaultGameData;
  UFUNCTION(BlueprintCallable)
  void AddToPool(EGolemAllegiance Allegiance, AGolem* Golem);
  UFUNCTION(BlueprintCallable)
  void RemoveFromPool(EGolemAllegiance Allegiance, AGolem* Golem);
  UPROPERTY(BlueprintReadOnly)
    TArray<TObjectPtr<AGolem>> FriendlyGolems;
  UPROPERTY(BlueprintReadOnly)
    TArray<TObjectPtr<AGolem>> EnemyGolems;
  UPROPERTY(BlueprintReadOnly)
    TArray<TObjectPtr<AGolem>> NeutralGolems;

	UPROPERTY(BlueprintAssignable)
	FOnPoolUpdated OnPoolUpdated;
};
