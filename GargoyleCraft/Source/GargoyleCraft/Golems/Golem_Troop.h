#pragma once

#include "CoreMinimal.h"
#include "Golem.h"
#include "Golem_Troop.generated.h"

class UPDA_Golem;
class UC_Drop;

UCLASS()
class AGolem_Troop : public AGolem
{
    GENERATED_BODY()
public:
	virtual void Init_Implementation(UPDA_Golem* PDAGolem, FVector FirstTargetLocation) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnFinishedCreated_Implementation() override;

		virtual void UpdateTargetLocation_Implementation(FVector NewTargetLocation);

	//SelectableInterface
	virtual AActor* Selected_Implementation(AGC_PC_RTS* PlayerController) override;
	virtual AActor* Unselected_Implementation(AGC_PC_RTS* PlayerController) override;

	virtual void SetTarget(AActor* _Target) override;

	virtual void TryActivateAbility() override;

	//---Events Attributes
	virtual void OnDeath_Implementation() override;
	//---
	//-----TooltipInterface
	virtual FTooltipData GetTooltip_Implementation(UObject* WorldContext) override;
};