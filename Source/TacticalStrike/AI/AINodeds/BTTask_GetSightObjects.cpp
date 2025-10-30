// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_GetSightObjects.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "AI/AIController/TeamMainAI.h"

UBTTask_GetSightObjects::UBTTask_GetSightObjects()
{
	NodeName = TEXT("GetSightObjects");
}

EBTNodeResult::Type UBTTask_GetSightObjects::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DefaultUnit)
		return EBTNodeResult::Failed;
	UWorld* World = DefaultUnit->GetWorld();
	FVector Center = DefaultUnit->GetActorLocation();
	float DetectRadius = 3000.0f;

	if (nullptr == World)
		return EBTNodeResult::Failed;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, DefaultUnit);
	if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Blue)
	{
		bool bResult = World->OverlapMultiByChannel(
			OverlapResults,
			Center,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel6,
			FCollisionShape::MakeSphere(DetectRadius),
			CollisionQueryParam
		);

		if (bResult)
		{
			for (const auto Results : OverlapResults)
			{
				if (Cast<ADefaultUnit>(Results.GetActor()) != nullptr)
				{
					ADefaultUnit* TargetActor = Cast<ADefaultUnit>(Results.GetActor());
					ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(OwnerComp.GetAIOwner());
					ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(DefaultUnitAI->GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::MainTeamAIKey));
					if (TeamMainAI != nullptr)
					{
						TeamMainAI->SightEnemyArr.AddUnique(TargetActor);
					}
				}
			}
		}
	}
	else if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Red)
	{
		bool bResult = World->OverlapMultiByChannel(
			OverlapResults,
			Center,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel7,
			FCollisionShape::MakeSphere(DetectRadius),
			CollisionQueryParam
		);
		if (bResult)
		{
			for (const auto Results : OverlapResults)
			{
				if (Cast<ADefaultUnit>(Results.GetActor()) != nullptr)
				{
					ADefaultUnit* TargetActor = Cast<ADefaultUnit>(Results.GetActor());
					ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(OwnerComp.GetAIOwner());
					ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(DefaultUnitAI->GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::MainTeamAIKey));

					if (TeamMainAI != nullptr)
					{
						TeamMainAI->SightEnemyArr.AddUnique(TargetActor);
					}
				}
			}

		}
	}
	else
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::DefaultUnitAI_bSightTriggerActivatedKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::UnitActionTriggerKey, false);

	return EBTNodeResult::Succeeded;
	
}