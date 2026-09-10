// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_CommandAI_DecisionHavior.h"
#include "AI/AIController/CommanderAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Objects/Buildings/DefaultBuilding.h"

UBTTask_CommandAI_DecisionHavior::UBTTask_CommandAI_DecisionHavior()
{
	NodeName = TEXT("CommandAI_DecisionHavior");
}

EBTNodeResult::Type UBTTask_CommandAI_DecisionHavior::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());

	int8 AIHaviorSequenceIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey);
	TArray<FHaviorStateSequence> HaviorStateSequenceQueue = CommanderAI->HaviorStateSequenceQueue;

	for (int8 i = AIHaviorSequenceIndex; i < HaviorStateSequenceQueue.Num(); i++)
	{
		if (i == INDEX_NONE)
			continue;

		if (HaviorStateSequenceQueue[i].AIHaviorState == EAIBehaviorState::None)
		{
			continue;
		}
		else if (HaviorStateSequenceQueue[i].AIHaviorState == EAIBehaviorState::Waiting)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey, i);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<int8>(CommanderAI->HaviorStateSequenceQueue[i].HaviorCode));
			return EBTNodeResult::Succeeded;
		}
		else if (HaviorStateSequenceQueue[i].AIHaviorState == EAIBehaviorState::Waiting_Building && HaviorStateSequenceQueue[i].IsHaviorChecked == false)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey, i);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<int8>(CommanderAI->HaviorStateSequenceQueue[i].HaviorCode));
			return EBTNodeResult::Succeeded;
		}
		else if (HaviorStateSequenceQueue[i].AIHaviorState == EAIBehaviorState::Waiting_Territory && HaviorStateSequenceQueue[i].IsHaviorChecked == false)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey, i);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<int8>(CommanderAI->HaviorStateSequenceQueue[i].HaviorCode));
			return EBTNodeResult::Succeeded;
		}
		else if (HaviorStateSequenceQueue[i].AIHaviorState == EAIBehaviorState::Failed_Lack_Resource)
		{
			if (HaviorStateSequenceQueue[i].IsHaviorChecked == false)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey, i);
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<int8>(CommanderAI->HaviorStateSequenceQueue[i].HaviorCode));
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey, HaviorStateSequenceQueue.Num() - 1);
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<int8>(EAIBehaviorCode::Havior_TurnEnd));
				return EBTNodeResult::Succeeded;
			}
		}
		else if (HaviorStateSequenceQueue[i].AIHaviorState == EAIBehaviorState::TurnEnd)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey, i);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<int8>(EAIBehaviorCode::Havior_TurnEnd));
			return EBTNodeResult::Succeeded;
		}
	}

	////명령 큐를 첫 번째부터 탐색
	//for (const FHaviorStateSequence HaviorStateSequence : CommanderAI->HaviorStateSequenceQueue)
	//{
	//	//탐색된 명령이 '대기 중' 일 경우해당 명령을 실행
	//	if (HaviorStateSequence.AIHaviorState == EAIBehaviorState::Waiting)
	//	{
	//		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<uint8>(HaviorStateSequence.HaviorCode));
	//		return EBTNodeResult::Succeeded;
	//	}
	//	//탐색된 명령이 '해당 명령을 실행할 건물이 활성화되길 기다리는 중' 일 경우 건물 활성화 시 명령 실행,
	//	//  아직 비활성화 시 대기하고 다시 배열 탐색, 건물 파괴 시 실행 건물 다시 탐색
	//	else if (HaviorStateSequence.AIHaviorState == EAIBehaviorState::Waited_Building)
	//	{
	//		if (HaviorStateSequence.SpawnBuilding.IsValid())
	//		{
	//			if (HaviorStateSequence.SpawnBuilding->ObjectState == EObjectState::Activated)
	//			{
	//				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<uint8>(HaviorStateSequence.HaviorCode));
	//				return EBTNodeResult::Succeeded;
	//			}
	//			else if (HaviorStateSequence.SpawnBuilding->ObjectState == EObjectState::DeActivated)
	//			{
	//				continue;
	//			}
	//		}
	//		else
	//		{

	//		}
	//	}
	//}

	return EBTNodeResult::Succeeded;
}