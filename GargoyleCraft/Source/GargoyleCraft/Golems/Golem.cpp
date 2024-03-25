#include "Golem.h"

#include "ActorTransactionAnnotation.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"

AGolem::AGolem()
{
  Root = CreateDefaultSubobject<USceneComponent>("Root");
  SetRootComponent(Root);
  GetCapsuleComponent()->SetupAttachment(Root);
  PoolComponent = CreateDefaultSubobject<UC_Pool>("PoolComponent");
  AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("GolemASC");
}

void AGolem::UpdateTargetLocation(FVector NewTargetLocation)
{
  CurrentTargetLocation = NewTargetLocation;
  Cast<AAIController>(this)->MoveToLocation(CurrentTargetLocation);
}