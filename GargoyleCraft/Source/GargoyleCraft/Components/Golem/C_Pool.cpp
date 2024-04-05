#include "C_Pool.h"

#include "GargoyleCraft/GameFramework/RTS/GC_GS_RTS.h"
#include "GargoyleCraft/Golems/Golem.h"

void UC_Pool::BeginPlay()
{
  Super::BeginPlay();
  AddToPool();
}

void UC_Pool::AddToPool()
{
  GET_GS_RTS()->AddToPool(GolemAllegiance, Cast<AGolem>(GetOwner()));
}

void UC_Pool::RemoveFromPool()
{
  GET_GS_RTS()->RemoveFromPool(GolemAllegiance, Cast<AGolem>(GetOwner()));
}
