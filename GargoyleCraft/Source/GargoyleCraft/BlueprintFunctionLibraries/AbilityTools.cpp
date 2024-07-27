// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTools.h"

#include "GargoyleCraft/GameFramework/RTS/GC_GS_RTS.h"
#include "GargoyleCraft/Golems/Golem.h"

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

		case Enemy:
			GolemsToSearch.Append(WorldContextObject->GetWorld()->GetGameState<AGC_GS_RTS>()->EnemyGolems);

		case Neutral:
			GolemsToSearch.Append(WorldContextObject->GetWorld()->GetGameState<AGC_GS_RTS>()->NeutralGolems);
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
	if(returnGolem)
	{
		UE_LOG(LogTemp, Warning, TEXT("FindNearestGolem %s"), *returnGolem->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FindNearestGolem nullptr"));
	}
	return returnGolem;
}
