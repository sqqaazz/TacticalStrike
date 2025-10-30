// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRedTamplePos.h"
#include "Characters/Units/RifleMan/RifleManAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindRedTamplePos::UBTTask_FindRedTamplePos()
{
	NodeName = TEXT("FindRedTamplePos");
}

EBTNodeResult::Type UBTTask_FindRedTamplePos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ARifleManAI::SpawnPosKey);
	FNavLocation NextPos;

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ARifleManAI::MovingPosKey, NextPos.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
