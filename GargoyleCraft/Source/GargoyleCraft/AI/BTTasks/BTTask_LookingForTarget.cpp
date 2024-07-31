// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LookingForTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GargoyleCraft/BlueprintFunctionLibraries/AbilityTools.h"
#include "GargoyleCraft/Golems/Golem.h"

UBTTask_LookingForTarget::UBTTask_LookingForTarget(const FObjectInitializer& objectInitializer)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_LookingForTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
	//auto pawn = Cast<AAIController>(OwnerComp.GetOwner())->GetPawn();
	//;
	//auto target = UAbilityTools::FindNearestGolem(OwnerComp.GetOwner(), pawn, pawn->GetComponentByClass<UC_Pool>()->HostileDiplomacies, 500);
	////UAIBlueprintHelperLibrary::GetBlackboard(OwnerComp.GetOwner())->SetValueAsObject("Target", target);
	//if(target)
	//	return EBTNodeResult::Succeeded;
	//else
	//{
	//	EBTNodeResult::Failed;
	//}
}