	#include "Golem_Troop.h"

#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "Data/PDA_Golem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "GargoyleCraft/GameFramework/RTS/GC_PC_RTS.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayAbilities/GC_GameplayAbility_Character.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_ActivateAbility.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_MoveForced.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_Target.h"
#include "GargoyleCraft/Include/GC_Macros.h"
#include "GargoyleCraft/Include/GC_Structs.h"
#include "GargoyleCraft/Components/Golem/C_Drop.h"

#include "NavigationSystem.h"
#include <GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h>


void AGolem_Troop::Init_Implementation(UPDA_Golem* PDAGolem, FVector FirstTargetLocation)
{
	Super::Init_Implementation(PDAGolem, FirstTargetLocation);
}


void AGolem_Troop::BeginPlay()
{
  Super::BeginPlay();
}

void AGolem_Troop::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	DrawDebugCircle(GetWorld(), GetActorLocation(), AbilitySystemComponent->GetSet<UAttributeSet_Character>()->GetAggroRange(), 50, FColor::Red, false, -1, 0, 0, FVector(0,1,0), FVector(1,0,0), false);

	if(!AbilitySystemComponent->HasMatchingGameplayTag(MAKE_TAG("State.Moving.Forced")))
	{
		if(Target)
		{
			if(AbilitySystemComponent->HasMatchingGameplayTag(MAKE_TAG("State.Targeting")) 
				&& !AbilitySystemComponent->HasMatchingGameplayTag(MAKE_TAG("State.Ability.Ongoing"))
				&& !AbilitySystemComponent->HasMatchingGameplayTag(MAKE_TAG("State.Ability.InRange")))
			{
				if (PoolComponent->GolemAllegiance == EGolemAllegiance::Ally)
				{
					UE_LOG(LogTemp, Warning, TEXT("MoveToLocation"));
				}
				auto controller = Cast<AAIController>(GetController());
				if (ensure(controller))
				{
					controller->MoveToLocation(Target->GetActorLocation());
				}
			}
		}
	}
}

void AGolem_Troop::OnFinishedCreated_Implementation()
{
	Super::OnFinishedCreated_Implementation();
}

void AGolem_Troop::UpdateTargetLocation_Implementation(FVector NewTargetLocation)
{
	Super::UpdateTargetLocation_Implementation(NewTargetLocation);
	CurrentTargetLocation = NewTargetLocation;
	// Get the Navigation System
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys) return;

	FNavLocation NearestLocation;
	float SearchRadius = 2000.f;
	bool bFoundLocation = NavSys->ProjectPointToNavigation(CurrentTargetLocation,NearestLocation, FVector(SearchRadius));
	CurrentTargetLocation = NearestLocation;
	auto controller = Cast<AAIController>(GetController());
	if(ensure(controller))
	{
		controller->MoveToLocation(CurrentTargetLocation);
		ApplyMoveForced();
	}
}

AActor* AGolem_Troop::Selected_Implementation(AGC_PC_RTS* PlayerController)
{
	PlayerController->AddToSelectedGolems(this);
	return this;
}
AActor* AGolem_Troop::Unselected_Implementation(AGC_PC_RTS* PlayerController)
{
	PlayerController->RemoveFromSelectedGolems(this);
	return this;
}

void AGolem_Troop::ReachLocationTick_Implementation()
{
	Super::ReachLocationTick_Implementation();
}

void AGolem_Troop::SetTarget(AActor* _Target)
{
	Target = _Target;
	if(_Target)
	{
		auto context = GetAbilitySystemComponent()->MakeEffectContext();
		auto spec = GetAbilitySystemComponent()->MakeOutgoingSpec(UGE_Target::StaticClass(), 1, context);
		TargetEffect = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*spec.Data);
	}else
	{
		GetAbilitySystemComponent()->RemoveActiveGameplayEffect(TargetEffect);
	}

}

void AGolem_Troop::TryActivateAbility()
{
	Super::TryActivateAbility();
	if (Target)
	{
		if (AbilitySystemComponent->HasMatchingGameplayTag(MAKE_TAG("State.Targeting")) 
			&& !AbilitySystemComponent->HasMatchingGameplayTag(MAKE_TAG("State.Ability.Ongoing")))
		{
			for(auto abilityData : AbilitySystemComponent->Abilities)
			{
				if(abilityData.Range >= FVector::Distance(GetActorLocation(), Target->GetActorLocation()))
				{
					AbilitySystemComponent->AddLooseGameplayTag(MAKE_TAG("State.Ability.InRange"));
					if (AbilitySystemComponent->HasMatchingGameplayTag(abilityData.CooldownTag))
						continue;
					if(AbilitySystemComponent->TryActivateAbility(abilityData.AbilityHandle))
					{
						auto controller = Cast<AAIController>(GetController());
						if (ensure(controller))
						{
							controller->StopMovement();
						}
					}
					break;
				}
				else 
				{
					if (PoolComponent->GolemAllegiance == EGolemAllegiance::Ally) 
					{
						UE_LOG(LogTemp, Warning, TEXT("Remove InRange Tag"));
					}
					AbilitySystemComponent->RemoveLooseGameplayTag(MAKE_TAG("State.Ability.InRange"));
				}
			}
		}
	}
}

void AGolem_Troop::OnDeath_Implementation()
{
	Super::OnDeath_Implementation();
	Execute_Unselected(this, Cast<AGC_PC_RTS>(GetWorld()->GetFirstPlayerController()));
	DropComponent->SpawnLoot();
	Destroy();
}

FTooltipData AGolem_Troop::GetTooltip_Implementation(UObject* WorldContext)
{
	Super::GetTooltip_Implementation(WorldContext);
	FTooltipData returnData;
	returnData.Title = DataAsset->TooltipData.Title;
	returnData.Icon = DataAsset->TooltipData.Icon;
	returnData.Flavor = DataAsset->TooltipData.Flavor;

	FFormatNamedArguments Args;
	Args.Add(TEXT("OriginalDesc"), DataAsset->TooltipData.Description);
	Args.Add(TEXT("Attributes"), UGC_TooltipLibrary::GetTooltipDataFromAbilitySystemComponent(this, AbilitySystemComponent).Description);
	returnData.Description = FText::Format(NSLOCTEXT("Golem", "Golem.Tooltip", "{OriginalDesc}\n{Attributes}"), Args);
	

	return returnData;
}
