#include "Golem.h"

#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "Data/PDA_Golem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"

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

void AGolem::OnFinishedCreated()
{
	UpdateTargetLocation(CurrentTargetLocation);
	DataAsset->Apply(this);
	const UAttributeSet_Character* set = AbilitySystemComponent->GetSet<UAttributeSet_Character>();
	auto name = set->GetName();
	if (ensure(AbilitySystemComponent))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAttributeSet_Character::GetMovementSpeedAttribute()).AddUObject(this, &AGolem::OnSpeedChanged);
		GetCharacterMovement()->MaxWalkSpeed = AbilitySystemComponent->GetSet<UAttributeSet_Character>()->GetMovementSpeed();
		GetCharacterMovement()->MaxAcceleration = AbilitySystemComponent->GetSet<UAttributeSet_Character>()->GetMovementSpeed();
	}
}

void AGolem::UpdateTargetLocation(FVector NewTargetLocation)
{
  CurrentTargetLocation = NewTargetLocation;
  auto controller = Cast<AAIController>(GetController());
  if(ensure(controller))
    controller->MoveToLocation(CurrentTargetLocation);
}

void AGolem::OnSpeedChanged(const FOnAttributeChangeData& Values)
{
  GetCharacterMovement()->MaxWalkSpeed = Values.NewValue;
  GetCharacterMovement()->MaxAcceleration = Values.NewValue;
}
