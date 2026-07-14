// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_FinishAIHavior.h"
#include "AI/AIController/CommanderAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FinishAIHavior::UBTTask_FinishAIHavior()
{
	NodeName = TEXT("CommandAI_FinishAIHavior");
}

EBTNodeResult::Type UBTTask_FinishAIHavior::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());

	int8 AIHaviorSequenceIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey);
	FHaviorStateSequence HaviorStateSequenceQueue = CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex];

	if (HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Successed)
	{
		CommanderAI->HaviorStateSequenceQueue.RemoveAt(AIHaviorSequenceIndex);
		return EBTNodeResult::Succeeded;
	}
	else if (HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Failed_Lack_Resource)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey, CommanderAI->HaviorStateSequenceQueue.Num() - 1);
		return EBTNodeResult::Succeeded;
	}
	else if (HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Waited_Building)
	{
		return EBTNodeResult::Succeeded;
	}

	//CommanderAI->HaviorStateSequenceQueue.RemoveAt(AIHaviorSequenceIndex);
	//if (AIHaviorSequenceIndex == CommanderAI->HaviorStateSequenceQueue.Num())
	//{
	//	AIHaviorSequenceIndex == INDEX_NONE;
	//	OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey, AIHaviorSequenceIndex);
	//}

	return EBTNodeResult::Succeeded;
}