// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_CombatAI_CommandTeamUnits.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "AI/AIController/TeamMainAI.h"


UBTTask_CombatAI_CommandTeamUnits::UBTTask_CombatAI_CommandTeamUnits()
{
	NodeName = TEXT("CombatAI_CommandTeamUnits");
}

EBTNodeResult::Type UBTTask_CombatAI_CommandTeamUnits::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CurOwnerComp = &OwnerComp;
	ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetAIOwner());
	if (TeamMainAI != nullptr)
	{
		TArray<ADefaultUnit*> TeamUnitArr = TeamMainAI->TeamUnitArr;
		int32 CurrentUnitIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ATeamMainAI::TeamMainAI_TeamUnitIndexKey);
		bool bSightTriggerActivatedKey = OwnerComp.GetBlackboardComponent()->GetValueAsBool(ATeamMainAI::TeamMainAI_bSightTriggerActivatedKey);
		if (CurrentUnitIndex == INDEX_NONE)
		{
			return EBTNodeResult::Succeeded;
		}

		ADefaultUnit* DefaultUnit = TeamUnitArr[CurrentUnitIndex];
		//UE_LOG(LogTemp, Log, TEXT("%s"), *DefaultUnit->GetName());
		if (DefaultUnit != nullptr)
		{
			ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(DefaultUnit->GetController());
			if (DefaultUnitAI != nullptr)
			{
				if (bSightTriggerActivatedKey)
					DefaultUnitAI->GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::DefaultUnitAI_bSightTriggerActivatedKey, true);
				else
					DefaultUnitAI->GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::DefaultUnitAI_bSightTriggerActivatedKey, false);

				DefaultUnitAI->UnitTurnEndDelegate.AddUniqueDynamic(this, &UBTTask_CombatAI_CommandTeamUnits::FinishUnithaviorTask);
				DefaultUnitAI->GetBlackboardComponent()->SetValueAsInt(ADefaultUnitAI::ActionCountKey, 2);
				DefaultUnitAI->StartUnitTurn();
				DefaultUnitAI->LifeTime++;
				return EBTNodeResult::InProgress;
			}
		}
	}

	return EBTNodeResult::Failed;
}

void UBTTask_CombatAI_CommandTeamUnits::FinishUnithaviorTask()
{
	FinishLatentTask(*CurOwnerComp, EBTNodeResult::Succeeded);
}