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
