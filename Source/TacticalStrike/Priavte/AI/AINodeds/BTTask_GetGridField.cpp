// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_GetGridField.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"

UBTTask_GetGridField::UBTTask_GetGridField()
{
	NodeName = TEXT("GetGridField");
}

EBTNodeResult::Type UBTTask_GetGridField::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(OwnerComp.GetAIOwner());
	if (DefaultUnitAI == nullptr)
		return EBTNodeResult::Failed;

	DefaultUnitAI->GetGridField();
	return EBTNodeResult::Succeeded;

}