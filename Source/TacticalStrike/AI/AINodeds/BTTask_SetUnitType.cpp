// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetUnitType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
//#include "UnitDataTables.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"


UBTTask_SetUnitType::UBTTask_SetUnitType()
{
	NodeName = TEXT("SetUnitType");
}

EBTNodeResult::Type UBTTask_SetUnitType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance != nullptr)
		UnitDataTable = GameInstance->GetAllUnitTable();

	UnitDataTable.Sort([](const FUnitTableRow& Results1, const FUnitTableRow& Results2) {
		return Results1.Tech < Results2.Tech;
	});

	float TimeWeight = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::TimeWeightKey);

	float RandomValue = FMath::Clamp(FMath::RandRange(0.0f, float(UnitDataTable.Num())) * TimeWeight, 0.0f, float(UnitDataTable.Num()));

	//UE_LOG(LogTemp, Log, TEXT("Unit1Weight: %d"), UnitDataTable[0]->UnitType);
	//UE_LOG(LogTemp, Log, TEXT("Unit2Weight: %d"), UnitDataTable[1]->UnitType);
	//UE_LOG(LogTemp, Log, TEXT("Unit3Weight: %d"), UnitDataTable[2]->UnitType);
	//UE_LOG(LogTemp, Log, TEXT("TimeWeight: %f"), RandomValue);

	for (uint8 i = 0; i < UnitDataTable.Num(); i++)
	{
		if (RandomValue < 0.1f)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::UnitTypeKey, UnitDataTable[i]->UnitType);
			break;
		}
		if (i > RandomValue)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::UnitTypeKey, UnitDataTable[i]->UnitType);
			break;
		}
	}


	return EBTNodeResult::Succeeded;
}