#include "Golem.h"

#include "ActorTransactionAnnotation.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGolem::AGolem()
{
  SetRootComponent(GetCapsuleComponent());
  /*Root = CreateDefaultSubobject<USceneComponent>("Root");
  SetRootComponent(Root);
  GetCapsuleComponent()->SetupAttachment(Root);*/
  PoolComponent = CreateDefaultSubobject<UC_Pool>("PoolComponent");
  AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("GolemASC");
}
