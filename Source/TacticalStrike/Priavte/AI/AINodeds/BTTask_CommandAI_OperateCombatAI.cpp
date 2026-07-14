// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_CommandAI_OperateCombatAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CommanderUnit.h"
#include "AI/AIController/CommanderAI.h"

UBTTask_CommandAI_OperateCombatAI::UBTTask_CommandAI_OperateCombatAI()
{
	NodeName = TEXT("CommandAI_OperateCombatAI");
}

EBTNodeResult::Type UBTTask_CommandAI_OperateCombatAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CurOwnerComp = &OwnerComp;
	ACommanderUnit* CommanderUnit = Cast<ACommanderUnit>(OwnerComp.GetAIOwner()->GetPawn());

	if (CommanderUnit != nullptr)
	{
		CommanderUnit->TeamMainAIInstance->CombatAIEndActionDelegate.AddUniqueDynamic(this, &UBTTask_CommandAI_OperateCombatAI::FinishCombatAIhaviorTask);
		CommanderUnit->TeamMainAIInstance->StartAction();
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_CommandAI_OperateCombatAI::FinishCombatAIhaviorTask()
{
	CurOwnerComp->GetBlackboardComponent()->SetValueAsBool(ACommanderAI::bIsAICommandingKey, true);
	FinishLatentTask(*CurOwnerComp, EBTNodeResult::Succeeded);
}