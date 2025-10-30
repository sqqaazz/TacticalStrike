// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTService_GetSightObjects.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "AI/AIController/TeamMainAI.h"

UBTService_GetSightObjects::UBTService_GetSightObjects()
{
	NodeName = TEXT("Service_GetSightObjects");
	//Interval = 0.3f;
}

void UBTService_GetSightObjects::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DefaultUnit)
		return;
	UWorld* World = DefaultUnit->GetWorld();
	FVector Center = DefaultUnit->GetActorLocation();
	float DetectRadius = 3000.0f;

	if (nullptr == World)
		return;
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
			//OverlapResults.Sort([DefaultUnit](const FOverlapResult& Results1, const FOverlapResult& Results2) {
			//	return Results1.GetActor()->GetDistanceTo(DefaultUnit) < Results2.GetActor()->GetDistanceTo(DefaultUnit);
			//});

			for (auto Results : OverlapResults)
			{
				if (Cast<ADefaultUnit>(Results.GetActor()) != nullptr)
				{
					ADefaultUnit* TargetActor = Cast<ADefaultUnit>(Results.GetActor());
					//int32 ResultsX = TargetActor->GetActorLocation().X / 100;
					//int32 ResultsY = TargetActor->GetActorLocation().Y / 100;

					ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetAIOwner());
					//FSightEnemyStruct SightEnemyStruct = { FIntPoint[ResultsX, ResultsY], TargetActor->ObjectInfo };
					if (TeamMainAI != nullptr)
					{
						TeamMainAI->SightEnemyArr.AddUnique(TargetActor);
					}
				}
			}

			/*auto Object = OverlapResults[0].GetActor();
			if (Object->ActorHasTag("RedTeamUnit") || Object->ActorHasTag("RedTeamBuilding"))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::TargetKey, Object);
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ADefaultUnitAI::DistanceKey, Object->GetDistanceTo(ControllingPawn));
				return;
			}*/

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
			for (auto Results : OverlapResults)
			{
				if (Cast<ADefaultUnit>(Results.GetActor()) != nullptr)
				{
					ADefaultUnit* TargetActor = Cast<ADefaultUnit>(Results.GetActor());
					//int32 ResultsX = TargetActor->GetActorLocation().X / 100;
					//int32 ResultsY = TargetActor->GetActorLocation().Y / 100;

					ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetAIOwner());
					//FSightEnemyStruct SightEnemyStruct = { FIntPoint[ResultsX, ResultsY], TargetActor->ObjectInfo };
					if (TeamMainAI != nullptr)
					{
						TeamMainAI->SightEnemyArr.AddUnique(TargetActor);
					}
				}
			}

			//OverlapResults.Sort([ControllingPawn](const FOverlapResult& Results1, const FOverlapResult& Results2) {
			//	return Results1.GetActor()->GetDistanceTo(ControllingPawn) < Results2.GetActor()->GetDistanceTo(ControllingPawn);
			//});

			//auto Object = OverlapResults[0].GetActor();

			//if (Object->ActorHasTag("BlueTeamUnit") || Object->ActorHasTag("BlueTeamBuilding"))
			//{
			//	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::TargetKey, Object);
			//	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ADefaultUnitAI::DistanceKey, Object->GetDistanceTo(ControllingPawn));
			//	return;
			//}

			return;

		}
	}
	else
		return;

}
