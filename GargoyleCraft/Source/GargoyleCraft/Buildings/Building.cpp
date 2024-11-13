#include "Building.h"
#include "Components/ArrowComponent.h"
#include "GargoyleCraft/GameInstance/GC_PlayerDataSubsystem.h"
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

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->OnDataInitialized.AddDynamic(this, &ABuilding::Initialize);
}

bool ABuilding::RequestGolemCreation(TSoftObjectPtr<UPDA_Golem> Data)
{
  //Golem automatically added in pool via its component UC_Pool
	auto subsysystem = GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>();
	if (!subsysystem->PayResource(ResourceTag, Data->GetCost())) 
	{
		return false;
	}
	auto tempGolem = GetWorld()->SpawnActorDeferred<AGolem>(Data->GolemClass, GolemSpawnPoint->GetComponentTransform());
	tempGolem->Init(Data.LoadSynchronous(), GolemSpawnFlag->GetComponentLocation());
	UGameplayStatics::FinishSpawningActor(tempGolem, GolemSpawnPoint->GetComponentTransform());
	return true;
}

AActor* ABuilding::Selected_Implementation(AGC_PC_RTS* PlayerController)
{
	return this;
}

AActor* ABuilding::Unselected_Implementation(AGC_PC_RTS* PlayerController)
{
	return this;
}

void ABuilding::Initialize_Implementation(FPlayerData DataSent)
{
	if (Initialized)
		return;
	IInitializable::Initialize_Implementation(DataSent);
	Initialized = true;
	GetWorld()->GetGameInstance()->GetSubsystem<UGC_PlayerDataSubsystem>()->OnDataInitialized.RemoveDynamic(this, &ABuilding::Initialize);
}