// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Units/DefaultUnit/BTTask_DefaultUnit_EndUnitTurn.h"
#include "Characters/Units//DefaultUnit/DefaultUnitAI.h"


UBTTask_DefaultUnit_EndUnitTurn::UBTTask_DefaultUnit_EndUnitTurn()
{
	NodeName = TEXT("DefaultUnit_EndUnitTurn");
}

EBTNodeResult::Type UBTTask_DefaultUnit_EndUnitTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	if (DefaultUnitAI != nullptr)
	{
		DefaultUnitAI->EndUnitTurn();
		DefaultUnitAI->BrainComponent->StopLogic("Unit Turn End");
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}