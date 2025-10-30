// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetTimeWeight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"

UBTTask_SetTimeWeight::UBTTask_SetTimeWeight()
{
	NodeName = TEXT("SetTimeWeight");
}

EBTNodeResult::Type UBTTask_SetTimeWeight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);


	float CurrentTimeWeight = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::TimeWeightKey);
	float NewTimeWeight = FMath::Clamp(CurrentTimeWeight + 0.01f, 0.0f, 3.0f);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::TimeWeightKey, NewTimeWeight);

	return EBTNodeResult::Succeeded;
}