// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RifleMan_TurnToTarget.h"
#include "RifleManAI.h"
#include "RifleMan.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RifleMan_TurnToTarget::UBTTask_RifleMan_TurnToTarget()
{
	NodeName = TEXT("RifleManTurn");
}

EBTNodeResult::Type UBTTask_RifleMan_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto RifleMan = Cast<ARifleMan>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == RifleMan)
		return EBTNodeResult::Failed;

	auto Target = Cast<ARifleMan>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ARifleManAI::TargetKey));
	if (nullptr == Target)
	{
		auto DefaultTarget = Cast<ADefaultUnit>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ARifleManAI::TargetKey));
		if (nullptr == DefaultTarget)
		{
			return EBTNodeResult::Failed;
		}
		else
		{
			FVector LookVector = DefaultTarget->GetActorLocation() - RifleMan->GetActorLocation();
			LookVector.Z = 0.0f;
			FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
			RifleMan->SetActorRotation(FMath::RInterpTo(RifleMan->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));
			return EBTNodeResult::Succeeded;
		}
	}

	FVector LookVector = Target->GetActorLocation() - RifleMan->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	RifleMan->SetActorRotation(FMath::RInterpTo(RifleMan->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));
	return EBTNodeResult::Succeeded;
}