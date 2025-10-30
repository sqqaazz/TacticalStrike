// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_SetGridField.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"

UBTTask_SetGridField::UBTTask_SetGridField()
{
	NodeName = TEXT("SetGridField");
}

EBTNodeResult::Type UBTTask_SetGridField::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	/*ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(OwnerComp.GetAIOwner());
	if (DefaultUnitAI == nullptr)
		return EBTNodeResult::Failed;
	
	DefaultUnitAI->GetGridField();
	*/
	return EBTNodeResult::Succeeded;
	
}