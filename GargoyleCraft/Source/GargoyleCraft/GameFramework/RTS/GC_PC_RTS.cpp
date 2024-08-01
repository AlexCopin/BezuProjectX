#include "GC_PC_RTS.h"

#include "GargoyleCraft/Golems/Golem.h"

void AGC_PC_RTS::AddToSelectedGolems(AGolem* Golem)
{
	if(ensureAlways(Golem))
	{
		SelectedGolems.Add(Golem);
		OnGolemAdded.Broadcast(Golem);
		OnTargetsUpdated.Broadcast(this);
	}
}

void AGC_PC_RTS::RemoveFromSelectedGolems(AGolem* Golem)
{
	if (ensureAlways(Golem))
	{
		SelectedGolems.Remove(Golem);
		OnGolemRemoved.Broadcast(Golem);
		OnTargetsUpdated.Broadcast(this);
	}
}
