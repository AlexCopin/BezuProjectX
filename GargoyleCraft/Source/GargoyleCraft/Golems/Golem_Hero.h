#pragma once

#include "CoreMinimal.h"
#include "Golem.h"
#include "Golem_Hero.generated.h"

UCLASS()
class AGolem_Hero : public AGolem
{
    GENERATED_BODY()
public:
	virtual void Init_Implementation(UPDA_Golem* PDAGolem, FVector FirstTargetLocation) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnFinishedCreated_Implementation() override;
	virtual void UpdateTargetLocation_Implementation(FVector NewTargetLocation) override;
  //AbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	//SelectableInterface
	virtual AActor* Selected_Implementation(AGC_PC_RTS* PlayerController) override;
	virtual AActor* Unselected_Implementation(AGC_PC_RTS* PlayerController) override;

    virtual void OnSpeedChanged(const FOnAttributeChangeData& Values) override;
	virtual void SetTarget(AActor* _Target) override;

	//Put it into ASC
	virtual void TryActivateAbility() override;

	//---Events Attributes
	virtual void OnDeath_Implementation() override;
	//---

	//-----TooltipInterface
	virtual FTooltipData GetTooltip_Implementation(UObject* WorldContext) override;
protected:
	virtual void ReachLocationTick_Implementation() override;
};