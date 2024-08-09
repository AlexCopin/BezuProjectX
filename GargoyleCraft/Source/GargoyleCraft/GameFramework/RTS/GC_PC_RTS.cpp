#include "GC_PC_RTS.h"

#include "GargoyleCraft/Golems/Golem.h"

void AGC_PC_RTS::AddToSelectedGolems(AGolem* Golem)
{
	if(ensureAlways(Golem))
	{
		if(Golem->PoolComponent->GolemAllegiance == Ally)
		{
			ControlableGolems.Add(Golem);
		}else
		{
			for(int i = SelectedGolems.Num() - 1; i >= 0; i--)
			{
				ISelectable::Execute_Unselected(SelectedGolems[i], this);
			}
		}
		SelectedGolems.Add(Golem);
		OnGolemAdded.Broadcast(Golem);
		OnTargetsUpdated.Broadcast(this);
	}
}

void AGC_PC_RTS::RemoveFromSelectedGolems(AGolem* Golem)
{
	if (ensureAlways(Golem))
	{
		if (Golem->PoolComponent->GolemAllegiance == Ally)
		{
			ControlableGolems.Remove(Golem);
		}
		SelectedGolems.Remove(Golem);
		OnGolemRemoved.Broadcast(Golem);
		OnTargetsUpdated.Broadcast(this);
	}
}
