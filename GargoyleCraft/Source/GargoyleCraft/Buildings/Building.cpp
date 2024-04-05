#include "Building.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

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
  //Golem automatically added in pool via its component UC_Pool
  auto tempGolem = GetWorld()->SpawnActorDeferred<AGolem>(Data->GolemClass, GolemSpawnPoint->GetComponentTransform());
  tempGolem->AbilitySystemComponent->DefaultStartingData.Append(Data->DefaultStartingData);
  UGameplayStatics::FinishSpawningActor(tempGolem, GolemSpawnPoint->GetComponentTransform());
  tempGolem->Init();
  tempGolem->UpdateTargetLocation(GolemSpawnFlag->GetComponentLocation());
  }
