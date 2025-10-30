// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RifleManAttack.h"
#include "RifleManAI.h"
#include "RifleMan.h"

UBTTask_RifleManAttack::UBTTask_RifleManAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_RifleManAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//auto RifleMan = Cast<ARifleMan>(OwnerComp.GetAIOwner()->GetPawn());
	//if (nullptr == RifleMan)
	//	return EBTNodeResult::Failed;
	//RifleMan->Attack();
	//IsAttacking = true;
	//RifleMan->OnAttackEnd.AddLambda([this]() -> void {
	//	IsAttacking = false;
	//	});
	return EBTNodeResult::InProgress;
}

void UBTTask_RifleManAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}