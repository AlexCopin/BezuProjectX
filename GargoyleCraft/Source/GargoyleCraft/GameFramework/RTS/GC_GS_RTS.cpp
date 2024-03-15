// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_GS_RTS.h"


void AGC_GS_RTS::AddToPool(EGolemAllegiance Allegiance, AGolem* Golem)
{
  if(!Golem)
  {
    return;
  }
  switch (Allegiance)
  {
    case EGolemAllegiance::Ally:
      FriendlyGolems.Add(Golem);
    break;
    case EGolemAllegiance::Enemy:
      EnemyGolems.Add(Golem);
      break;
    case EGolemAllegiance::Neutral:
      NeutralGolems.Add(Golem);
      break;
  }
}
