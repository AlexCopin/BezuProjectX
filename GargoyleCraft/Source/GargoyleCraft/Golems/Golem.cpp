	#include "Golem.h"

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

AGolem::AGolem()
{
  SetRootComponent(GetCapsuleComponent());
  PoolComponent = CreateDefaultSubobject<UC_Pool>("PoolComponent");
  AbilitySystemComponent = CreateDefaultSubobject<UGC_AbilitySystemComponent>("GolemASC");
  DropComponent = CreateDefaultSubobject<UC_Drop>("DropComponent");
}

void AGolem::Init_Implementation(UPDA_Golem* PDAGolem, FVector FirstTargetLocation)
{
	DataAsset = PDAGolem;
	CurrentTargetLocation = FirstTargetLocation;
}


void AGolem::BeginPlay()
{
  Super::BeginPlay();
  OnFinishedCreated();
}

void AGolem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGolem::OnFinishedCreated_Implementation()
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
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Character::GetMovementSpeedAttribute()).AddUObject(this, &AGolem::OnSpeedChanged);
		GetCharacterMovement()->MaxWalkSpeed = set->GetMovementSpeed();
		GetCharacterMovement()->MaxAcceleration = set->GetMovementSpeed();

		//TIMER TRY ACTIVATE ABILITY (AVOID FRAMERATE TICKING)
		GetWorld()->GetTimerManager().SetTimer(TimerTryActivateAbility, this, &AGolem::TryActivateAbility, 0.15f, true);

		//Events Attributes
		AbilitySystemComponent->ASC_OnDeath.AddDynamic(this, &AGolem::AGolem::OnDeath);

		GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->ApplyRecipeOnGolem(this);
	}

}

void AGolem::UpdateTargetLocation_Implementation(FVector NewTargetLocation)
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

AActor* AGolem::Selected_Implementation(AGC_PC_RTS* PlayerController)
{
	PlayerController->AddToSelectedGolems(this);
	return this;
}
AActor* AGolem::Unselected_Implementation(AGC_PC_RTS* PlayerController)
{
	PlayerController->RemoveFromSelectedGolems(this);
	return this;
}


void AGolem::OnSpeedChanged(const FOnAttributeChangeData& Values)
{
  GetCharacterMovement()->MaxWalkSpeed = Values.NewValue;
  GetCharacterMovement()->MaxAcceleration = Values.NewValue;
}

void AGolem::ApplyMoveForced()
{
	if (ForcedMoveEffect.IsValid())
		return;
	auto context = GetAbilitySystemComponent()->MakeEffectContext();
	auto spec = GetAbilitySystemComponent()->MakeOutgoingSpec(UGE_MoveForced::StaticClass(), 1, context);
	ForcedMoveEffect = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*spec.Data);

	if (ForcedMoveEffect.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("AGolem::ApplyMoveForced"));
		GetWorld()->GetTimerManager().SetTimer(TimerReachLocation, this, &AGolem::ReachLocationTick, 0.2f, true);
	}
}


void AGolem::ReachLocationTick_Implementation()
{
	if (ForcedMoveEffect.IsValid())
	{
		if (GetMovementComponent()->Velocity.Length() <= 0.1f)
		{
			RemoveMoveForced();
		}
	}
}
void AGolem::RemoveMoveForced()
{
	if (ForcedMoveEffect.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("AGolem::RemoveMoveForced"));
		GetAbilitySystemComponent()->RemoveActiveGameplayEffect(ForcedMoveEffect);
		ForcedMoveEffect.Invalidate();
		GetWorld()->GetTimerManager().ClearTimer(TimerReachLocation);
	}
}

void AGolem::SetTarget(AActor* _Target)
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

void AGolem::TryActivateAbility()
{
}

void AGolem::OnDeath_Implementation()
{
	Destroy();
}

FTooltipData AGolem::GetTooltip_Implementation(UObject* WorldContext)
{
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
