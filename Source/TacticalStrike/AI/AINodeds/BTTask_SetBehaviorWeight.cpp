// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetBehaviorWeight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AIController/CommanderAI.h"

UBTTask_SetBehaviorWeight::UBTTask_SetBehaviorWeight()
{
	NodeName = TEXT("SetBehaviorWeight");
}

EBTNodeResult::Type UBTTask_SetBehaviorWeight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	TArray<float> WeightItems;

	//가중치 높을수록 전선 밀림, 유닛 생산
	float BattleFrontWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BattleFrontWeightKey);
	//가중치 높을수록 자원 생산
	float TimeWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::TimeWeightKey);

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
	WeightItems.Add(TimeWeightKey);

	for (uint8 i = 0; i < WeightItems.Num(); i++)
	{
		CurrentNum += WeightItems[i];
		if (CurrentNum >= RandomNum)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::BehaviorWeightKey, i);
			UE_LOG(LogTemp, Log, TEXT("Total: %f, Behavior: %d"), TotalWeight, i);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}