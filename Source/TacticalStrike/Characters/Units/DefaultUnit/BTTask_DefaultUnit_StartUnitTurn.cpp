// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Units/DefaultUnit/BTTask_DefaultUnit_StartUnitTurn.h"
#include "Characters/Units//DefaultUnit/DefaultUnitAI.h"


UBTTask_DefaultUnit_StartUnitTurn::UBTTask_DefaultUnit_StartUnitTurn()
{
	NodeName = TEXT("DefaultUnit_StartUnitTurn");
}

EBTNodeResult::Type UBTTask_DefaultUnit_StartUnitTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	if (DefaultUnitAI != nullptr)
	{
		DefaultUnitAI->BrainComponent->RestartLogic();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
