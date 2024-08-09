#include "Golem.h"

#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "Data/PDA_Golem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GargoyleCraft/GameFramework/RTS/GC_PC_RTS.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_MoveForced.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_Target.h"
#include "GargoyleCraft/Include/GC_Macros.h"

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
	DrawDebugCircle(GetWorld(), GetActorLocation(), AbilitySystemComponent->GetSet<UAttributeSet_Character>()->GetAggroRange(), 50, FColor::Red, false, -1, 0, 0, FVector(0,1,0), FVector(1,0,0), false);

	if(AbilitySystemComponent->HasMatchingGameplayTag(MAKE_TAG("State.Moving.Forced")))
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.1f, FColor::Red, "Moving Forced");
	}else
	{
		if(Target)
		{
			if(AbilitySystemComponent->HasMatchingGameplayTag(MAKE_TAG("State.Targeting")))
			{
				auto controller = Cast<AAIController>(GetController());
				if (ensure(controller))
				{
					controller->MoveToLocation(Target->GetActorLocation());
				}
			}
		}
	}
}

void AGolem::OnFinishedCreated()
{
	if(ensure(DataAsset))
	{
		UpdateTargetLocation(CurrentTargetLocation);
		DataAsset->Apply(GetAbilitySystemComponent());
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
