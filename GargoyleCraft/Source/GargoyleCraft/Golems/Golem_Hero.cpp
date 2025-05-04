#include "Golem_Hero.h"

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


void AGolem_Hero::Init_Implementation(UPDA_Golem* PDAGolem, FVector FirstTargetLocation)
{
	Super::Init_Implementation(PDAGolem, FirstTargetLocation);
}


void AGolem_Hero::BeginPlay()
{
  Super::BeginPlay();
}

void AGolem_Hero::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGolem_Hero::OnFinishedCreated_Implementation()
{
	if (ensure(AbilitySystemComponent))
	{
		const UAttributeSet_Character* set = AbilitySystemComponent->GetSet<UAttributeSet_Character>();
		if(PoolComponent->GolemAllegiance == Ally)
		{
			AbilitySystemComponent->InitAbilityActorInfo(GetWorld()->GetFirstPlayerController()->GetPawn(), this);
		}
		if (ensure(DataAsset))
		{
			UpdateTargetLocation(CurrentTargetLocation);
			DataAsset->Apply(GetAbilitySystemComponent());
		}
		AbilitySystemComponent->ApplyDefaultValues();
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Character::GetMovementSpeedAttribute()).AddUObject(this, &AGolem_Hero::OnSpeedChanged);
		GetCharacterMovement()->MaxWalkSpeed = set->GetMovementSpeed();
		GetCharacterMovement()->MaxAcceleration = set->GetMovementSpeed();

		//TIMER TRY ACTIVATE ABILITY (AVOID FRAMERATE TICKING)
		GetWorld()->GetTimerManager().SetTimer(TimerTryActivateAbility, this, &AGolem_Hero::TryActivateAbility, 0.15f, true);

		//Events Attributes
		AbilitySystemComponent->ASC_OnDeath.AddDynamic(this, &AGolem_Hero::AGolem_Hero::OnDeath);

		GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->ApplyRecipeOnGolem(this);
	}

}

void AGolem_Hero::UpdateTargetLocation_Implementation(FVector NewTargetLocation)
{
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

AActor* AGolem_Hero::Selected_Implementation(AGC_PC_RTS* PlayerController)
{
	return Super::Selected_Implementation(PlayerController);
}
AActor* AGolem_Hero::Unselected_Implementation(AGC_PC_RTS* PlayerController)
{
	return Super::Unselected_Implementation(PlayerController);
}


void AGolem_Hero::OnSpeedChanged(const FOnAttributeChangeData& Values)
{
	Super::OnSpeedChanged(Values);
}

void AGolem_Hero::ReachLocationTick_Implementation()
{
	Super::ReachLocationTick_Implementation();
}

void AGolem_Hero::SetTarget(AActor* _Target)
{
	Super::SetTarget(_Target);
}

void AGolem_Hero::TryActivateAbility()
{
	Super::TryActivateAbility();
}

void AGolem_Hero::OnDeath_Implementation()
{
	Destroy();
}

FTooltipData AGolem_Hero::GetTooltip_Implementation(UObject* WorldContext)
{
	return Super::GetTooltip_Implementation(WorldContext);
}
