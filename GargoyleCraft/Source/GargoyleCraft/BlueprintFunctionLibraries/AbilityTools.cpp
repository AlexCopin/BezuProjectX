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
	if(auto GS = WorldContextObject->GetWorld()->GetGameState<AGC_GS_RTS>())
	{
		TArray<AGolem*> GolemsToSearch;
		for (int i = 0; i < AllegiancesToSearch.Num(); i++)
		{
			switch (AllegiancesToSearch[i])
			{
			case Ally:
				GolemsToSearch.Append(GS->FriendlyGolems);
				break;
			case Enemy:
				GolemsToSearch.Append(GS->EnemyGolems);
				break;
			case Neutral:
				GolemsToSearch.Append(GS->NeutralGolems);
				break;
			}
		}
		AGolem* returnGolem = nullptr;
		float closestDistance = FLT_MAX;
		FVector originLocation = From->GetActorLocation();
		for (auto golem : GolemsToSearch)
		{
			auto tempDist = FVector::Distance(originLocation, golem->GetActorLocation());
			if (closestDistance > tempDist && tempDist <= Range)
			{
				closestDistance = tempDist;
				returnGolem = golem;
			}
		}
		return returnGolem;
	}
	return nullptr;
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
	/*int maxRows = 5;
	int32 numRows = FMath::Min(maxRows, FMath::CeilToInt(FMath::Sqrt(static_cast<float>(NumPoints))));
	float colDivided = (float)NumPoints / (float)numRows;
	int32 numCol = FMath::CeilToInt(colDivided);*/

	int maxCol = 5;
	int32 numCol = FMath::Min(maxCol, FMath::CeilToInt(FMath::Sqrt(static_cast<float>(NumPoints))));
	float rowDivided = (float)NumPoints / (float)numCol;
	int32 numRows = FMath::CeilToInt(rowDivided);


	TArray<FVector> Locations;
	float rowOffset = 150;
	float columnsOffset = 150;

	// Calculate half-width and half-height offsets to center the rectangle
	FVector localCenter = FVector(rowOffset * (numRows-1) / 2, columnsOffset * (numCol-1) / 2, Center.Z);

	FVector direction = Center - StartingPoint;
	// Calculate the rotation required to align rectangle to the direction vector
	FRotator Rotation = direction.Rotation();

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCol; j++)
		{	
			FVector localPoint = FVector(i * rowOffset - localCenter.X, j * columnsOffset - localCenter.Y, Center.Z);
			FVector rotatedPoint = Rotation.RotateVector(localPoint);
			FVector finalPoint = Center + rotatedPoint;

			Locations.Add(finalPoint);
		}
	}

	return Locations;
}