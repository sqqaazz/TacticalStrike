// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DefaultUnit_TurnToTarget.h"
#include "DefaultUnitAI.h"
#include "DefaultUnit.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_DefaultUnit_TurnToTarget::UBTTask_DefaultUnit_TurnToTarget()
{
	NodeName = TEXT("DefaultUnitTurn");
}

EBTNodeResult::Type UBTTask_DefaultUnit_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DefaultUnit = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DefaultUnit)
		return EBTNodeResult::Failed;

	auto Target = Cast<ADefaultUnit>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::TargetKey));
	if (Target != nullptr)
	{
		FVector LookVector = Target->GetActorLocation() - DefaultUnit->GetActorLocation();
		LookVector.Z = 0.0f;
		FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
		DefaultUnit->SetActorRotation(FMath::RInterpTo(DefaultUnit->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));
		return EBTNodeResult::Succeeded;
	}
	else
		return EBTNodeResult::Failed;
	//if (nullptr == Target)
	//{
	//	auto DefaultTarget = Cast<ADefaultUnit>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ARifleManAI::TargetKey));
	//	if (nullptr == DefaultTarget)
	//	{
	//		return EBTNodeResult::Failed;
	//	}
	//	else
	//	{
	//		FVector LookVector = DefaultTarget->GetActorLocation() - RifleMan->GetActorLocation();
	//		LookVector.Z = 0.0f;
	//		FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	//		RifleMan->SetActorRotation(FMath::RInterpTo(RifleMan->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));
	//		return EBTNodeResult::Succeeded;
	//	}
	//}
}