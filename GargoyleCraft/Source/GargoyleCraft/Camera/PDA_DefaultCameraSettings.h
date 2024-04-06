// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_DefaultCameraSettings.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UPDA_DefaultCameraSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2f CameraZoomLimits;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CameraMoveSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CameraRotateSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CameraZoomSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CameraMovementLag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CameraRotationLag;
};
