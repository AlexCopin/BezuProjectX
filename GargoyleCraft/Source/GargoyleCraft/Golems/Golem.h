#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GargoyleCraft/Components/Golem/C_Pool.h"
#include "AbilitySystemInterface.h"
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Interfaces/Selectable.h"
#include "Golem.generated.h"

class UPDA_Golem;
class UC_Drop;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedCreated);

UCLASS()
class AGolem : public ACharacter, public IAbilitySystemInterface, public ISelectable
{
    GENERATED_BODY()
public:
	AGolem();
	UFUNCTION(BlueprintCallable)
		void Init(UPDA_Golem* PDAGolem, FVector FirstTargetLocation);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UC_Pool> PoolComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UGC_AbilitySystemComponent> AbilitySystemComponent;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UC_Drop> DropComponent;
	UFUNCTION()
		void OnFinishedCreated();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsSelected;

    UFUNCTION(BlueprintCallable)
		void UpdateTargetLocation(FVector NewTargetLocation);
    UFUNCTION(BlueprintCallable)
		FVector GetCurrentTargetLocation() { return CurrentTargetLocation; }
    UPROPERTY(BlueprintReadOnly)
		TObjectPtr<UPDA_Golem> DataAsset;
  //AbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	//SelectableInterface
	virtual AActor* Selected_Implementation(AGC_PC_RTS* PlayerController) override;
	virtual AActor* Unselected_Implementation(AGC_PC_RTS* PlayerController) override;

    void OnSpeedChanged(const FOnAttributeChangeData& Values);

	void ApplyMoveForced();
	void RemoveMoveForced();

	void SetTarget(AActor* _Target);
	TObjectPtr<AActor> GetTarget() { return Target; };

	void TryActivateAbility();

	//---Events Attributes
	UFUNCTION(BlueprintNativeEvent)
	void OnDeath();
	void OnDeath_Implementation();

	//---
private:

	TObjectPtr<AActor> Target = nullptr;

	bool IsMovingToTarget;
	UFUNCTION()
	void ReachLocationTick();

    FVector CurrentTargetLocation;
	FActiveGameplayEffectHandle ForcedMoveEffect;
	FActiveGameplayEffectHandle TargetEffect;

	FTimerHandle TimerReachLocation;
	FTimerHandle TimerTryActivateAbility;
};