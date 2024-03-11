#include "Building.h"
#include "Components/ArrowComponent.h"

ABuilding::ABuilding()
{
  Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
  SetRootComponent(Root);
  auto attachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
  GolemSpawnPoint = CreateDefaultSubobject<UArrowComponent>("GolemSpawnPoint");
  GolemSpawnPoint->AttachToComponent(Root, attachmentRules);
  GolemSpawnFlag = CreateDefaultSubobject<UArrowComponent>("GolemSpawnFlag");
  GolemSpawnFlag->AttachToComponent(Root, attachmentRules);
}

void ABuilding::RequestGolemCreation(UPDA_Golem* Data)
{
  auto tempGolem = GetWorld()->SpawnActorDeferred<AGolem>(Data->GolemClass, GolemSpawnPoint->GetComponentTransform());
  tempGolem->AbilitySystemComponent->DefaultStartingData.Append(Data->DefaultStartingData);
  //Call something to add in a pool -> pool will be used to look for selectable units when drag & drop (don't look every actors, just the actors in the pool)
}
