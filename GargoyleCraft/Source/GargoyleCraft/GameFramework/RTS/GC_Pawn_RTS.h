// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GC_Pawn_RTS.generated.h"

UCLASS()
class GARGOYLECRAFT_API AGC_Pawn_RTS : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGC_Pawn_RTS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
