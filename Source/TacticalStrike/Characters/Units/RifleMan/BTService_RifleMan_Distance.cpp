// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_RifleMan_Distance.h"
#include "RifleManAI.h"
#include "RifleMan.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_RifleMan_Distance::UBTService_RifleMan_Distance()
{
	NodeName = TEXT("RifleMan_Distance");
	Interval = 0.2f;
}

void UBTService_RifleMan_Distance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;
	auto Target = Cast<ARifleMan>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ARifleManAI::TargetKey));
	if (nullptr == Target)
		return;
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ARifleManAI::DistanceKey, Target->GetDistanceTo(ControllingPawn));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("DeltaHeight : %f"), Target->GetDistanceTo(ControllingPawn)));
	/*
	if (Target->GetDistanceTo(ControllingPawn) <= 1000.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ARifleManAI::DistanceKey, Target->GetDistanceTo(ControllingPawn));
	}*/
}