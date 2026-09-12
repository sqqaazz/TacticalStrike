// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_SetUnitType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
//#include "UnitDataTables.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "GameMode/TacticalStrikeGameStateBase.h"
#include "Kismet/GameplayStatics.h"


UBTTask_SetUnitType::UBTTask_SetUnitType()
{
	NodeName = TEXT("SetUnitType");
}

EBTNodeResult::Type UBTTask_SetUnitType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameStateBase = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());

	int8 AIHaviorSequenceIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey);
	FHaviorStateSequence HaviorStateSequenceQueue = CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex];

	if (HaviorStateSequenceQueue.IsHaviorChecked == true)
		return EBTNodeResult::Succeeded;
	

	if (HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Waiting_Building || HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Failed_Lack_Resource)
		return EBTNodeResult::Succeeded;

	if (GameInstance != nullptr)
		UnitDataTable = GameInstance->GetAllUnitTable();

	UnitDataTable.Sort([](const FUnitTableRow& Results1, const FUnitTableRow& Results2) {
		return Results1.Tech < Results2.Tech;
	});

	int32 Turn = GameStateBase->Turn;
	float MaxRand = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 100.0f), FVector2D(0.0f, UnitDataTable.Num() - 1), Turn);
	float RandomValue = FMath::RandRange(0.0f, MaxRand);
	//UE_LOG(LogTemp, Log, TEXT("RandomValue: %f"), RandomValue);
	for (uint8 i = 0; i < UnitDataTable.Num(); i++)
	{
		if (RandomValue < i + 1)
		{
			//UE_LOG(LogTemp, Log, TEXT("i: %d, UnitTyype: %d"), i, UnitDataTable[i]->UnitType);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::UnitTypeKey, UnitDataTable[i]->UnitType);
			break;
		}
		else
			continue;
	}


	//float TimeWeight = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::TimeWeightKey);
	//float RandomValue = FMath::Clamp(FMath::RandRange(0.0f, float(UnitDataTable.Num())) * TimeWeight, 0.0f, float(UnitDataTable.Num()));
	//for (uint8 i = 0; i < UnitDataTable.Num(); i++)
	//{
	//	if (RandomValue < 0.1f)
	//	{
	//		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::UnitTypeKey, UnitDataTable[i]->UnitType);
	//		break;
	//	}
	//	if (i > RandomValue)
	//	{
	//		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::UnitTypeKey, UnitDataTable[i]->UnitType);
	//		break;
	//	}
	//}


	return EBTNodeResult::Succeeded;
}