// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_GetTeamSight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/TeamMainAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"

UBTTask_GetTeamSight::UBTTask_GetTeamSight()
{
	NodeName = TEXT("GetTeamSight");
}

EBTNodeResult::Type UBTTask_GetTeamSight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetAIOwner());
	if (TeamMainAI == nullptr)
	{
		return EBTNodeResult::Failed;

	}

	TeamUnitArr = TeamMainAI->TeamUnitArr;

	for (const auto TeamUnit : TeamUnitArr)
	{
		ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(TeamUnit->GetController());
		if (DefaultUnitAI != nullptr)
		{
			DefaultUnitAI->GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::UnitActionTriggerKey, true);
			DefaultUnitAI->GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::DefaultUnitAI_bSightTriggerActivatedKey, true);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Units: %d"), TeamUnitArr.Num());
	return EBTNodeResult::Succeeded;

}