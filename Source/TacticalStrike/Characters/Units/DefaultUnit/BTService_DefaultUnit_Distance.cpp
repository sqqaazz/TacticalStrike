// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DefaultUnit_Distance.h"
#include "DefaultUnitAI.h"
#include "DefaultUnit.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_DefaultUnit_Distance::UBTService_DefaultUnit_Distance()
{
	NodeName = TEXT("DefaultUnit_Distance");
	Interval = 0.2f;
}

void UBTService_DefaultUnit_Distance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	/*auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;
	auto Target = Cast<ADefaultUnit>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::TargetKey));
	if (nullptr == Target)
		return;
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ADefaultUnitAI::DistanceKey, Target->GetDistanceTo(ControllingPawn));*/
	/*
	if (Target->GetDistanceTo(ControllingPawn) <= 1000.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ARifleManAI::DistanceKey, Target->GetDistanceTo(ControllingPawn));
	}*/
}
