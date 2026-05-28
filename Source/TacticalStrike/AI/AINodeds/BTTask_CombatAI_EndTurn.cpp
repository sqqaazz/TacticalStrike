// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_CombatAI_EndTurn.h"
#include "AI/AIController/TeamMainAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CombatAI_EndTurn::UBTTask_CombatAI_EndTurn()
{
	NodeName = TEXT("CombatAI_EndTurn");
}

EBTNodeResult::Type UBTTask_CombatAI_EndTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetAIOwner());
	int32 TeamUnitIndexKey = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ATeamMainAI::TeamMainAI_TeamUnitIndexKey);
	bool bSightTriggerActivatedKey = OwnerComp.GetBlackboardComponent()->GetValueAsBool(ATeamMainAI::TeamMainAI_bSightTriggerActivatedKey);
	if (TeamMainAI != nullptr)
	{
		TArray<ADefaultUnit*> TeamUnitArr = TeamMainAI->TeamUnitArr;
		if (TeamUnitArr.Num() == 0)
		{
			//TeamMainAI->BrainComponent->StopLogic("CombatAI Turn End");
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ATeamMainAI::TeamMainAI_bSightTriggerActivatedKey, false);
			TeamMainAI->EndAction();
			return EBTNodeResult::Succeeded;
		}

		if (bSightTriggerActivatedKey)
		{
			if (TeamUnitArr.Num() - 1 == TeamUnitIndexKey)
			{
				TeamUnitIndexKey = 0;
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ATeamMainAI::TeamMainAI_TeamUnitIndexKey, TeamUnitIndexKey);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ATeamMainAI::TeamMainAI_bSightTriggerActivatedKey, false);
				return EBTNodeResult::Succeeded;
			}
			else
			{
				TeamUnitIndexKey++;
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ATeamMainAI::TeamMainAI_TeamUnitIndexKey, TeamUnitIndexKey);
				return EBTNodeResult::Succeeded;
			}
		}
		else
		{
			if (TeamUnitArr.Num() - 1 == TeamUnitIndexKey)
			{
				TeamUnitIndexKey = 0;
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ATeamMainAI::TeamMainAI_TeamUnitIndexKey, TeamUnitIndexKey);
				TeamMainAI->EndAction();

				return EBTNodeResult::Succeeded;
			}
			else
			{
				TeamUnitIndexKey++;
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(ATeamMainAI::TeamMainAI_TeamUnitIndexKey, TeamUnitIndexKey);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}