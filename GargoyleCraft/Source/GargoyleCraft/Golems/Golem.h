#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GargoyleCraft/Components/Golem/C_Pool.h"
#include "AbilitySystemInterface.h"
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Golem.generated.h"

class UPDA_Golem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedCreated);

UCLASS()
class AGolem : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()
public:
	AGolem();
	UFUNCTION()
		void Init(UPDA_Golem* PDAGolem, FVector FirstTargetLocation);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UC_Pool> PoolComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UGC_AbilitySystemComponent> AbilitySystemComponent;
	UFUNCTION()
		void OnFinishedCreated();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsSelected;

    UFUNCTION(BlueprintCallable)
		void UpdateTargetLocation(FVector NewTargetLocation);
    UFUNCTION(BlueprintCallable)
		FVector GetCurrentTargetLocation() { return CurrentTargetLocation; }
    UPROPERTY()
		TObjectPtr<UPDA_Golem> DataAsset;
  //AbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

    void OnSpeedChanged(const FOnAttributeChangeData& Values);

	void ApplyMoveForced();
	void RemoveMoveForced();
private:

	UFUNCTION()
	void ReachLocationTick();

    FVector CurrentTargetLocation;
	FActiveGameplayEffectHandle ForcedMoveEffect;

	FTimerHandle TimerReachLocation;
};