#include "GC_PC_RTS.h"

void AGC_PC_RTS::AddToSelectedGolems(AGolem* Golem)
{
  SelectedGolems.Add(Golem);
  OnGolemAdded.Broadcast(Golem);
}

void AGC_PC_RTS::RemoveFromSelectedGolems(AGolem* Golem)
{
  SelectedGolems.Remove(Golem);
  OnGolemRemoved.Broadcast(Golem);
}
