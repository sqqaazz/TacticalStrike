// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RifleManDetect.h"
#include "RifleManAI.h"
#include "RifleMan.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_RifleManDetect::UBTService_RifleManDetect()
{
	NodeName = TEXT("RifleMan_Detect");
	Interval = 0.5f;
}

void UBTService_RifleManDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

			auto Unit = OverlapResults[0].GetActor();
			if (Unit->ActorHasTag("RedTeamUnit"))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ARifleManAI::TargetKey, Unit);
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
			
			auto Unit = OverlapResults[0].GetActor();

			if (Unit->ActorHasTag("BlueTeamUnit"))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ARifleManAI::TargetKey, Unit);
				return;
			}

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
