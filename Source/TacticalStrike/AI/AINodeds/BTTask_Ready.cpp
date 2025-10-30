// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Ready.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAnim.h"

UBTTask_Ready::UBTTask_Ready()
{
	NodeName = TEXT("Detect_Ready");
}

EBTNodeResult::Type UBTTask_Ready::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ADefaultUnit* ControllingPawn = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn != nullptr)
	{
		UDefaultUnitAnim* ControllingPawnAnim = Cast<UDefaultUnitAnim>(ControllingPawn->GetMesh()->GetAnimInstance());
		if (ControllingPawnAnim != nullptr)
		{
			ControllingPawnAnim->DetectEnemy();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}