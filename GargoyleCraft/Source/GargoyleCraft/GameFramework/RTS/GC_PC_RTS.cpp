#include "GC_PC_RTS.h"

#include "GargoyleCraft/Golems/Golem.h"

bool AGC_PC_RTS::AddToSelectedGolems(AGolem* Golem)
{
	if(Golem->PoolComponent->GolemAllegiance == Ally)
	{
		SelectedGolems.Add(Golem);
		OnGolemAdded.Broadcast(Golem);
		return true;
	}
	return false;
}

void AGC_PC_RTS::RemoveFromSelectedGolems(AGolem* Golem)
{
  SelectedGolems.Remove(Golem);
  OnGolemRemoved.Broadcast(Golem);
}
