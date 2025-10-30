// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetBuildingType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"

UBTTask_SetBuildingType::UBTTask_SetBuildingType()
{
	NodeName = TEXT("SetBuildingType");
}

EBTNodeResult::Type UBTTask_SetBuildingType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	uint8 UnitType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::UnitTypeKey);
	uint8 UpgradeType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::UpgradeTypeKey);

	float UnitBuildingWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitBuildingWeightKey);
	float ResourceBuildingWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::ResourceBuildingWeightKey);

	BuildingWeightArr.Empty();
	BuildingWeightArr.Add(UnitBuildingWeightKey);
	BuildingWeightArr.Add(ResourceBuildingWeightKey);

	float TotalWeight = 0.0f;

	for (uint8 i = 0; i < BuildingWeightArr.Num(); i++)
		TotalWeight += BuildingWeightArr[i];

	float RandomValue = FMath::RandRange(0.0f, TotalWeight);

	float SelectedValue = 0.0f;
	
	UE_LOG(LogTemp, Log, TEXT("RandomValue: %f"), RandomValue);
	for (uint8 i = 0; i < BuildingWeightArr.Num(); i++)
	{
		SelectedValue += BuildingWeightArr[i];
		if (SelectedValue > RandomValue)
		{
			switch (i)
			{
			case 0:
				if (UnitType != 0)
				{
					if (GameInstance != nullptr)
						UnitDataTable = GameInstance->GetUnitTable(UnitType);

					uint8 UnitBuilding = UnitDataTable->ProductionBuilding;
					OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::BuildingTypeKey, UnitBuilding);
					return EBTNodeResult::Succeeded;
				}
				else
					return EBTNodeResult::Succeeded;
			case 1:
				if (UpgradeType != 0)
				{
					if (GameInstance != nullptr)
						UpgradeDataTable = GameInstance->GetUpgradeTable(UpgradeType);

					uint8 UpgradeBuilding = UpgradeDataTable->ProductionBuilding;
					UE_LOG(LogTemp, Log, TEXT("UpgradeBuilding!: %d"), UpgradeBuilding);
					OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::BuildingTypeKey, UpgradeBuilding);
				}
				else
					return EBTNodeResult::Succeeded;
			default:
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Succeeded;
}