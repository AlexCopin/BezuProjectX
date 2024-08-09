#include "Golem.h"

#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "Data/PDA_Golem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_MoveForced.h"

AGolem::AGolem()
{
  SetRootComponent(GetCapsuleComponent());
  PoolComponent = CreateDefaultSubobject<UC_Pool>("PoolComponent");
  AbilitySystemComponent = CreateDefaultSubobject<UGC_AbilitySystemComponent>("GolemASC");
}

void AGolem::Init(UPDA_Golem* PDAGolem, FVector FirstTargetLocation)
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

void AGolem::OnFinishedCreated()
{
	if(ensure(DataAsset))
	{
		UpdateTargetLocation(CurrentTargetLocation);
		DataAsset->Apply(this);
	}

	if (ensure(AbilitySystemComponent))
	{
		const UAttributeSet_Character* set = AbilitySystemComponent->GetSet<UAttributeSet_Character>();
		AbilitySystemComponent->ApplyDefaultValues();
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Character::GetMovementSpeedAttribute()).AddUObject(this, &AGolem::OnSpeedChanged);
		GetCharacterMovement()->MaxWalkSpeed = set->GetMovementSpeed();
		GetCharacterMovement()->MaxAcceleration = set->GetMovementSpeed();
	}
}

void AGolem::UpdateTargetLocation(FVector NewTargetLocation)
{
  CurrentTargetLocation = NewTargetLocation;
  auto controller = Cast<AAIController>(GetController());
  if(ensure(controller))
  {
	  controller->MoveToLocation(CurrentTargetLocation);
	  ApplyMoveForced();
  }
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


void AGolem::ReachLocationTick()
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
