// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_Pawn_RTS.h"

// Sets default values
AGC_Pawn_RTS::AGC_Pawn_RTS()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGC_Pawn_RTS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGC_Pawn_RTS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGC_Pawn_RTS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

