// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTools.h"

#include "GargoyleCraft/GameFramework/RTS/GC_GS_RTS.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_Damage.h"
#include "GargoyleCraft/Golems/Golem.h"
#include "GargoyleCraft/Include/GC_Macros.h"

AGolem* UAbilityTools::FindNearestGolem(const UObject* WorldContextObject, const AActor* From,
                                        TArray<TEnumAsByte<EGolemAllegiance>> AllegiancesToSearch, float Range)
{
	TArray<AGolem*> GolemsToSearch;
	for(int i = 0; i < AllegiancesToSearch.Num(); i++)
	{
		switch(AllegiancesToSearch[i])
		{
		case Ally :
			GolemsToSearch.Append(WorldContextObject->GetWorld()->GetGameState<AGC_GS_RTS>()->FriendlyGolems);
			break;
		case Enemy:
			GolemsToSearch.Append(WorldContextObject->GetWorld()->GetGameState<AGC_GS_RTS>()->EnemyGolems);
			break;
		case Neutral:
			GolemsToSearch.Append(WorldContextObject->GetWorld()->GetGameState<AGC_GS_RTS>()->NeutralGolems);
			break;
		}
	}
	AGolem* returnGolem = nullptr;
	float closestDistance = FLT_MAX;
	FVector originLocation = From->GetActorLocation();
	for(auto golem : GolemsToSearch)
	{
		auto tempDist = FVector::Distance(originLocation, golem->GetActorLocation());
		if(closestDistance > tempDist && tempDist <= Range)
		{
			closestDistance = tempDist;
			returnGolem = golem;
		}
	}
	return returnGolem;
}

void UAbilityTools::ApplyDamage(UAbilitySystemComponent* Source, UAbilitySystemComponent* Target, float Value)
{
	auto context = Source->MakeEffectContext();
	auto spec = Source->MakeOutgoingSpec(UGE_Damage::StaticClass(), 1, context);
	FGameplayEffectAttributeCaptureDefinition captDef;
	captDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	captDef.AttributeToCapture = UAttributeSet_Character::GetMetaDamageAttribute();
	spec.Data->CapturedRelevantAttributes.AddCaptureDefinition(captDef);
	spec.Data->SetSetByCallerMagnitude(MAKE_TAG("MetaDamage.Value"), Value);
	Source->ApplyGameplayEffectSpecToTarget(*spec.Data, Target);

}

TArray<FVector> UAbilityTools::CalculateRectanglePoints(FVector StartingPoint, FVector Center, int NumPoints, float Width, float Height, int NumColumns, int NumRows)
{
	TArray<FVector> Locations;
	float rowOffset = (NumRows - 1) == 0 ? 0 : Height / (NumRows - 1);
	float columnsOffset = (NumColumns - 1) == 0 ? 0 : Width / (NumColumns - 1);

	// Calculate half-width and half-height offsets to center the rectangle
	FVector localCenter = FVector(Height / 2, Width / 2, Center.Z);

	FVector direction = Center - StartingPoint;
	// Calculate the rotation required to align rectangle to the direction vector
	FRotator Rotation = direction.Rotation();

	for (int i = 0; i < NumRows; i++)
	{
		for (int j = 0; j < NumColumns; j++)
		{
			// Local space point in the rectangle centered around the origin
			FVector localPoint = FVector(i * rowOffset - localCenter.X, j * columnsOffset - localCenter.Y, Center.Z);
			// Rotate point to align the rectangle along the direction
			FVector rotatedPoint = Rotation.RotateVector(localPoint);
			// Translate rotated point to the rectangle center
			FVector finalPoint = Center + rotatedPoint;

			// Stop if we’ve generated the required number of points
			if (Locations.Num() >= NumPoints)
			{
				return Locations;
			}
			Locations.Add(finalPoint);
		}
	}

	return Locations;
}