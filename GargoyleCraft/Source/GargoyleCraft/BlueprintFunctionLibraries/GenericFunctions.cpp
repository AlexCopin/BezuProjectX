// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericFunctions.h"

FVector UGenericFunctions::CalculateRandomNormalizedDirectionFromLocation(const UObject* WorldContextObject, const FVector& Location, bool IsGround)
{
	float RandomAngleDegrees = FMath::FRandRange(0.0f, 360.0f);
	float RandomAngleRadians = FMath::DegreesToRadians(RandomAngleDegrees);
	// Calculate direction vector
	FVector DirectionVector = FVector::ZeroVector;
	DirectionVector.X = FMath::Cos(RandomAngleRadians);
	if(IsGround)
	{
		DirectionVector.Z = FMath::Sin(RandomAngleRadians);
		DirectionVector.Y = 0.0f;
	}else
	{
		DirectionVector.Y = FMath::Sin(RandomAngleRadians);
		DirectionVector.Z = 0.0f;
	}
	DirectionVector.Normalize();
    return DirectionVector;
}
