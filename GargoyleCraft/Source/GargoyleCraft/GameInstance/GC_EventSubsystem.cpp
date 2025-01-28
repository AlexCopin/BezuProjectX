// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_EventSubsystem.h"

#include "GargoyleCraft/Events/GC_EventActor.h"

void UGC_EventSubsystem::LaunchMonsterEvent(FMonsterEventData Data,FVector CenterLocation, float NewDuration /* = -1*/)
{
	auto eventActor = GetWorld()->SpawnActor<AGC_EventActor>(AGC_EventActor::StaticClass(), CenterLocation, FRotator::ZeroRotator);
	if (NewDuration > -1)
		Data.Duration = NewDuration;
	eventActor->Init(Data);
}
