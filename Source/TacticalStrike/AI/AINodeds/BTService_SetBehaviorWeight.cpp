// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetBehaviorWeight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"

UBTService_SetBehaviorWeight::UBTService_SetBehaviorWeight()
{
	NodeName = TEXT("SetBehaviorWeight");
	Interval = 0.1f;
}

void UBTService_SetBehaviorWeight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//가중치 높을수록 전선 밀림, 유닛 생산
	float BattleFrontWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BattleFrontWeightKey);
	//가중치 높을수록 자원 생산
	float TimeWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::TimeWeightKey);

	//UE_LOG(LogTemp, Log, TEXT("WeightLine: %f"), BattleFrontWeightKey);

	//가중치 가져옴
	float BuildWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BuildWeightKey);
	float UnitWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitWeightKey);
	float ResourceWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::ResourceWeightKey);

	float TotalWeight = BattleFrontWeightKey + BuildWeightKey + UnitWeightKey + ResourceWeightKey;

	//가중치 정하기
	float RandomNum = FMath::FRandRange(0.0f, TotalWeight);
	float CurrentNum = 0.0f;

	WeightItems.Add(BattleFrontWeightKey);
	WeightItems.Add(UnitWeightKey);
	WeightItems.Add(BuildWeightKey);
	WeightItems.Add(ResourceWeightKey);


	for (uint8 i = 0; i < WeightItems.Num(); i++)
	{
		CurrentNum += WeightItems[i];
		if (CurrentNum >= RandomNum)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::BehaviorWeightKey, i);
			UE_LOG(LogTemp, Log, TEXT("Total: %f, Behavior: %d"), TotalWeight, i);
			break;
		}
	}
	
}