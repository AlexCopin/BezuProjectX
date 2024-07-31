// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GargoyleCraft/BlueprintFunctionLibraries/AbilityTools.h"
#include "GargoyleCraft/Components/Golem/C_Pool.h"
#include "GargoyleCraft/GameplayAbilitySystem/GC_AbilitySystemComponent.h"
#include "GargoyleCraft/GameplayAbilitySystem/AttributeSets/AttributeSet_Character.h"
#include "GargoyleCraft/Golems/Golem.h"

UBTService_SetTarget::UBTService_SetTarget()
{
	Interval = 0.3f;
}

void UBTService_SetTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto pawn = OwnerComp.GetAIOwner()->GetPawn();
	bool found;
	auto golem = UAbilityTools::FindNearestGolem(pawn, pawn, pawn->GetComponentByClass<UC_Pool>()->HostileDiplomacies, pawn->GetComponentByClass<UGC_AbilitySystemComponent>()->GetGameplayAttributeValue(UAttributeSet_Character::GetAggroRangeAttribute(), found));
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, golem);
	if(golem)
	{
		Cast<UBTTaskNode>(GetMyNode())->WrappedOnTaskFinished(OwnerComp, NodeMemory, EBTNodeResult::Succeeded);
	}
	else
	{
		Cast<UBTTaskNode>(GetMyNode())->WrappedOnTaskFinished(OwnerComp, NodeMemory, EBTNodeResult::Failed);
	}
}
