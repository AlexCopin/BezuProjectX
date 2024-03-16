#include "Golem.h"

AGolem::AGolem()
{
  PoolComponent = CreateDefaultSubobject<UC_Pool>("PoolComponent");
  AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("GolemASC");
}
