// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_LeaveLevel.h"
#include "Kismet/GameplayStatics.h"
#include <GargoyleCraft/BlueprintFunctionLibraries/AbilityTools.h>

// Sets default values
AGC_LeaveLevel::AGC_LeaveLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGC_LeaveLevel::BeginPlay()
{
	Super::BeginPlay();
	

}

void AGC_LeaveLevel::Initialize_Implementation(FPlayerData DataSent)
{
	Super::Initialize_Implementation(DataSent);
}

void AGC_LeaveLevel::StartLevelDeparture_Implementation()
{
	OnLevelDepartureStarted.Broadcast(LeaveDuration);
	GetWorld()->GetTimerManager().SetTimer(TimerBeforeDeparture, this, &AGC_LeaveLevel::GoToLevel, LeaveDuration, false);
}


void AGC_LeaveLevel::GoToLevel()
{
	if (ensure(LevelToGoTo)) 
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerBeforeDeparture);
		UGameplayStatics::OpenLevel(GetWorld(), LevelToGoTo->GetFName(), true);
	}
}

void AGC_LeaveLevel::CustomTick_Implementation()
{
	Super::CustomTick_Implementation();
	if (auto golem = UAbilityTools::FindNearestGolem(this, this, { EGolemAllegiance::Ally }, RangeScan))
	{
		OnGolemDetected.Broadcast(true);
	}
	else
	{
		OnGolemDetected.Broadcast(false);
	}
}
