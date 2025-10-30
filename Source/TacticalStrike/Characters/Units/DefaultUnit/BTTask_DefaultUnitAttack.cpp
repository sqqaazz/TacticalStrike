// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DefaultUnitAttack.h"
#include "DefaultUnitAI.h"
#include "DefaultUnit.h"

UBTTask_DefaultUnitAttack::UBTTask_DefaultUnitAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_DefaultUnitAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Unit = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Unit)
		return EBTNodeResult::Failed;
	Unit->Attacking();
	IsAttacking = true;
	Unit->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		});
	return EBTNodeResult::InProgress;
}

void UBTTask_DefaultUnitAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
