// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_CommandAI_SetAIHavior.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/TeamMainAI.h"
#include "Characters/CommanderUnit.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"

UBTTask_CommandAI_SetAIHavior::UBTTask_CommandAI_SetAIHavior()
{
	NodeName = TEXT("CommandAI_SetAIHavior");
}

EBTNodeResult::Type UBTTask_CommandAI_SetAIHavior::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	ACommanderUnit* CommanderUnit = Cast<ACommanderUnit>(OwnerComp.GetAIOwner()->GetPawn());
	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());
	ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(CommanderUnit->TeamMainAIInstance);
	TotalWeight = 100.0f;
	float RemainWeight = TotalWeight;
	TArray<FHaviorWeight> HaviorWeightArray;

	//이전 명령이 자원 부족으로 실패 시 해당 턴 명령 종료
	uint8 PreviousHaviorState = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey);
	if (static_cast<EAIBehaviorState>(PreviousHaviorState) == EAIBehaviorState::Failed_Lack_Resource)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<uint8>(EAIBehaviorCode::Havior_TurnEnd));
		return EBTNodeResult::Succeeded;
	}
	else if (static_cast<EAIBehaviorState>(PreviousHaviorState) == EAIBehaviorState::Failed_Lack_Building)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<uint8>(EAIBehaviorCode::Havior_SpawnBuilding_Unit));
		return EBTNodeResult::Succeeded;
	}
	else if (static_cast<EAIBehaviorState>(PreviousHaviorState) == EAIBehaviorState::Waited_Building)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<uint8>(EAIBehaviorCode::Havior_TurnEnd));
		return EBTNodeResult::Succeeded;
	}


	//이전 행동에 의한 명령 가중치 설정
	float PreviousHaviorWeight = 0.0f;
	PreviousHaviorWeight = GetPreviousHaviorWeight(OwnerComp, RemainWeight, HaviorWeightArray);
	RemainWeight -= PreviousHaviorWeight;


	float SpawnUnitWeight = GetSpawnUnitWeight(TeamMainAI->SightEnemyArr, TeamMainAI->TeamUnitArr, RemainWeight, HaviorWeightArray);
	RemainWeight -= SpawnUnitWeight;

	float TempWeight = RemainWeight;
	FHaviorWeight TempHaviorWeight;
	TempHaviorWeight.HaviorCode = EAIBehaviorCode::Havior_SpawnUnit;
	TempHaviorWeight.HaviorWeight = TempWeight;
	HaviorWeightArray.Add(TempHaviorWeight);

	float RandomWeight = FMath::RandRange(0.0f, TotalWeight);
	float CurrentWeight = 0.0f;

	for (const FHaviorWeight HaviorWeight : HaviorWeightArray)
	{
		UE_LOG(LogTemp, Log, TEXT("RandomWeight: %f, Havior: [%d, %f]"), RandomWeight, static_cast<uint8>(HaviorWeight.HaviorCode), HaviorWeight.HaviorWeight);
	}

	for (const FHaviorWeight HaviorWeight : HaviorWeightArray)
	{
		CurrentWeight += HaviorWeight.HaviorWeight;
		if (RandomWeight < CurrentWeight)
		{
			//OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::AIHaviorKey, static_cast<uint8>(HaviorWeight.HaviorCode));
			FHaviorStateSequence HaviorStateSequence;
			HaviorStateSequence.HaviorWaitingTurn = 0;
			HaviorStateSequence.HaviorCode = HaviorWeight.HaviorCode;
			HaviorStateSequence.AIHaviorState = EAIBehaviorState::Waiting;
			HaviorStateSequence.SpawnObjectType = ESpawnObject::None;

			CommanderAI->HaviorStateSequenceQueue.Add(HaviorStateSequence);
			break;
		}
		else
			continue;
	}


	return EBTNodeResult::Succeeded;

}

float UBTTask_CommandAI_SetAIHavior::GetSpawnUnitWeight(TArray<class AActor*> SightEnemyArr, TArray<class ADefaultUnit*> TeamUnitArr, float RemainWeight, TArray<FHaviorWeight>& HaviorWeightArr)
{
	int32 EnemyThreats = 0;
	int32 TeamThreats = 0;

	for (AActor* SightEnemy : SightEnemyArr)
	{
		ADefaultUnit* EnemyUnit = Cast<ADefaultUnit>(SightEnemy);
		if (EnemyUnit != nullptr)
		{
			EnemyThreats += EnemyUnit->Tech;
		}
		else
			continue;
	}
	for (ADefaultUnit* TeamUnit : TeamUnitArr)
	{
		TeamThreats += TeamUnit->Tech;
	}

	float ThreatsRatio = 0.0f;
	if (TeamThreats == 0)
		ThreatsRatio = 3.0f;
	else
		ThreatsRatio = EnemyThreats / TeamThreats;

	float SpawnUnitWeight = FMath::GetMappedRangeValueClamped(FVector2D(1.0f, 3.0f), FVector2D(30.0f, 95.0f), ThreatsRatio);
	SpawnUnitWeight = FMath::RoundToInt(SpawnUnitWeight * 10.0f) / 10.0f;
	SpawnUnitWeight = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, TotalWeight), FVector2D(0.0f, RemainWeight), SpawnUnitWeight);

	FHaviorWeight HaviorWeight;
	HaviorWeight.HaviorCode = EAIBehaviorCode::Havior_SpawnUnit;
	HaviorWeight.HaviorWeight = SpawnUnitWeight;
	HaviorWeightArr.Add(HaviorWeight);

	return SpawnUnitWeight;
}

float UBTTask_CommandAI_SetAIHavior::GetPreviousHaviorWeight(UBehaviorTreeComponent& OwnerComp, float RemainWeight, TArray<FHaviorWeight>& HaviorWeightArr)
{
	uint8 PreviousHaviorState = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey);
	float PreviousHaviorWeight = 0.0f;

	uint8 PreviousHavior = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::AIHaviorKey);
	//이전 명령 성공 시 혹은 이전 명령이 없다면 해당 행동 가중치 0으로 설정
	if (static_cast<EAIBehaviorCode>(PreviousHavior) == EAIBehaviorCode::Havior_Idle ||
		static_cast<EAIBehaviorState>(PreviousHaviorState) == EAIBehaviorState::Successed)
	{
		FHaviorWeight HaviorWeight;
		HaviorWeight.HaviorCode = EAIBehaviorCode::None;
		HaviorWeight.HaviorWeight = PreviousHaviorWeight;
		HaviorWeightArr.Add(HaviorWeight);
		return PreviousHaviorWeight;
	}

	PreviousHaviorWeight = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, TotalWeight), FVector2D(0.0f, RemainWeight), 50.0f);
	PreviousHaviorWeight = FMath::RoundToInt(PreviousHaviorWeight * 10.0f) / 10.0f;
	FHaviorWeight HaviorWeight;
	HaviorWeight.HaviorCode = static_cast<EAIBehaviorCode>(PreviousHavior);
	HaviorWeight.HaviorWeight = PreviousHaviorWeight;
	HaviorWeightArr.Add(HaviorWeight);

	return PreviousHaviorWeight;
}


float UBTTask_CommandAI_SetAIHavior::GetResearchWeight(float RemainWeight, TArray<FHaviorWeight>& HaviorWeightArr)
{
	float ResearchWeight = 0.0f;
	FHaviorWeight HaviorWeight;
	HaviorWeight.HaviorCode = EAIBehaviorCode::Havior_Research;
	HaviorWeight.HaviorWeight = ResearchWeight;

	return 0.0f;
}


float UBTTask_CommandAI_SetAIHavior::GetResourceWeight(float RemainWeight, TArray<FHaviorWeight>& HaviorWeightArr)
{
	float ResourceWeight = 0.0f;
	FHaviorWeight HaviorWeight;
	HaviorWeight.HaviorCode = EAIBehaviorCode::Havior_SpawnBuilding_Resource;
	HaviorWeight.HaviorWeight = ResourceWeight;

	return 0.0f;
}