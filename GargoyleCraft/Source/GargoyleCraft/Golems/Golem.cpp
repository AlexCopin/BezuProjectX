#include "Golem.h"

#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"

AGolem::AGolem()
{
  SetRootComponent(GetCapsuleComponent());
  PoolComponent = CreateDefaultSubobject<UC_Pool>("PoolComponent");
  AbilitySystemComponent = CreateDefaultSubobject<UGC_AbilitySystemComponent>("GolemASC");
}


void AGolem::BeginPlay()
{
  Super::BeginPlay();
  Init();
}
void AGolem::Init()
{
  GetCharacterMovement()->MaxWalkSpeed = AbilitySystemComponent->GetSet<UAttributeSet_Character>()->GetMovementSpeed();
}

void AGolem::UpdateTargetLocation(FVector NewTargetLocation)
{
  CurrentTargetLocation = NewTargetLocation;
  auto controller = Cast<AAIController>(GetController());
  if(ensure(controller))
    controller->MoveToLocation(CurrentTargetLocation);
}
