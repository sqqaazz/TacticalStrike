// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DefaultUnitDetect.h"
#include "DefaultUnitAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_DefaultUnitDetect::UBTService_DefaultUnitDetect()
{
	NodeName = TEXT("DefaultUnit_Detect");
	Interval = 0.3f;
}

void UBTService_DefaultUnitDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;
	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 3000.0f;

	if (nullptr == World)
		return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	if (ControllingPawn->ActorHasTag("BlueTeamUnit"))
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
			OverlapResults.Sort([ControllingPawn](const FOverlapResult& Results1, const FOverlapResult& Results2) {
				return Results1.GetActor()->GetDistanceTo(ControllingPawn) < Results2.GetActor()->GetDistanceTo(ControllingPawn);
				});

			auto Object = OverlapResults[0].GetActor();
			if (Object->ActorHasTag("RedTeamUnit") || Object->ActorHasTag("RedTeamBuilding"))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::TargetKey, Object);
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ADefaultUnitAI::DistanceKey, Object->GetDistanceTo(ControllingPawn));
				return;
			}


			//for (auto const& OverlapResult : OverlapResults)
			//{
			//	//ARifleMan* RifleMan = Cast<ARifleMan>(OverlapResult.GetActor());
			//	auto Unit = OverlapResult.GetActor();
			//	if (Unit->ActorHasTag("RedTeamUnit"))
			//	{
			//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ARifleManAI::TargetKey, Unit);
			//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BlueTeam"));
			//		//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
			//		//DrawDebugPoint(World, Unit->GetActorLocation(), 16, FColor::Blue, false, 0.2f);
			//		//DrawDebugLine(World, ControllingPawn->GetActorLocation(), Unit->GetActorLocation(), FColor::Blue, false, 0.2f);
			//		return;
			//	}
			//}
		}
	}
	else if (ControllingPawn->ActorHasTag("RedTeamUnit"))
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
			OverlapResults.Sort([ControllingPawn](const FOverlapResult& Results1, const FOverlapResult& Results2) {
				return Results1.GetActor()->GetDistanceTo(ControllingPawn) < Results2.GetActor()->GetDistanceTo(ControllingPawn);
				});

			auto Object = OverlapResults[0].GetActor();

			if (Object->ActorHasTag("BlueTeamUnit") || Object->ActorHasTag("BlueTeamBuilding"))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::TargetKey, Object);
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ADefaultUnitAI::DistanceKey, Object->GetDistanceTo(ControllingPawn));
				return;
			}

			return;

			/*
			for (auto const& OverlapResult : OverlapResults)
			{
				//ARifleMan* RifleMan = Cast<ARifleMan>(OverlapResult.GetActor());
				auto Unit = OverlapResult.GetActor();
				if (Unit->ActorHasTag("BlueTeamUnit"))
				{

					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ARifleManAI::TargetKey, Unit);
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RedTeam"));
					//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
					//DrawDebugPoint(World, Unit->GetActorLocation(), 16, FColor::Blue, false, 0.2f);
					//DrawDebugLine(World, ControllingPawn->GetActorLocation(), Unit->GetActorLocation(), FColor::Blue, false, 0.2f);
					return;
				}
			}*/
		}
	}
	else
		return;

}
