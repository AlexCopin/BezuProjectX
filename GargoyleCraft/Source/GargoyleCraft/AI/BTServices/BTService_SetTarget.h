// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetTarget.generated.h"

/**
 * 
 */
UCLASS()
class GARGOYLECRAFT_API UBTService_SetTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UBTService_SetTarget();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
