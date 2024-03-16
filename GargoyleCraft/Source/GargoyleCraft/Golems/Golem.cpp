#include "Golem.h"

#include "ActorTransactionAnnotation.h"
#include "Components/CapsuleComponent.h"

AGolem::AGolem()
{
  Root = CreateDefaultSubobject<USceneComponent>("Root");
  SetRootComponent(Root);
  GetCapsuleComponent()->SetupAttachment(Root);
  PoolComponent = CreateDefaultSubobject<UC_Pool>("PoolComponent");
  AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("GolemASC");
}
