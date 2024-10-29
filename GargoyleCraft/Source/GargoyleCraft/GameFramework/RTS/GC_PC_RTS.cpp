#include "GC_PC_RTS.h"

#include "GargoyleCraft/Golems/Golem.h"

void AGC_PC_RTS::AddToSelectedGolems(AGolem* Golem)
{
	if(ensureAlways(Golem))
	{
		if(Golem->PoolComponent->GolemAllegiance == Ally)
		{
			ControlableGolems.AddUnique(Golem);
		}else
		{
			for(int i = SelectedGolems.Num() - 1; i >= 0; i--)
			{
				ISelectable::Execute_Unselected(SelectedGolems[i], this);
			}
		}
		SelectedGolems.AddUnique(Golem);
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
void AGC_PC_RTS::TryToSelectGolemArray_Implementation(const TArray<AActor*>& Golems, bool bAdditive)
{
	SelectGolemArray(Golems, bAdditive);
}

void AGC_PC_RTS::SelectGolemArray(TArray<AActor*> Golems, bool bAdditive)
{
	if (!bAdditive) 
	{
		for (int i = SelectedGolems.Num() - 1; i >= 0; i--)
		{
			if (!Golems.Contains(SelectedGolems[i]))
			{
				ISelectable::Execute_Unselected(SelectedGolems[i], this);
			}
		}
	}
	for (auto golem : Golems)
	{
		ISelectable::Execute_Selected(golem, this);
	}
}
