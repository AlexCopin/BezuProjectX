// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookingForTarget.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UBTTask_LookingForTarget : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_LookingForTarget(const FObjectInitializer& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	TObjectPtr<AActor> Owner;
};
