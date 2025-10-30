// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnUnit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
//#include "AIBuildingInfoClass.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/BuildingClickableComponent.h"

UBTTask_SpawnUnit::UBTTask_SpawnUnit()
{
	NodeName = TEXT("SpawnUnit");
}

EBTNodeResult::Type UBTTask_SpawnUnit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//UAIBuildingInfoClass* AIBuildingInfoClass = Cast<UAIBuildingInfoClass>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACommanderAI::AIBuildingInfo));
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	uint8 UnitType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::UnitTypeKey);
	if (GameInstance != nullptr)
		UnitDataTable = GameInstance->GetUnitTable(UnitType);
	if (UnitType == 0)
		return EBTNodeResult::Succeeded;

	int32 CurrentResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
	if (UnitDataTable->Cost > CurrentResource)
	{
		float UnitWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitWeightKey);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, UnitWeightKey + 0.1f);
		//처음으로 돌아가기 위해 성공 반환
		return EBTNodeResult::Succeeded;
	}
	else
	{
		TArray<AActor*> BuildingArray;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultBuilding::StaticClass(), BuildingArray);

		for (uint8 i = 0; i < BuildingArray.Num(); i++)
		{
			ADefaultBuilding* SpawnBuilding = Cast<ADefaultBuilding>(BuildingArray[i]);
			if (SpawnBuilding != nullptr && SpawnBuilding->ActorHasTag("RedTeamBuildings") 
				&& SpawnBuilding->BuildingType == UnitDataTable->ProductionBuilding)
			{
				UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
					(SpawnBuilding->GetComponentByClass(UBuildingClickableComponent::StaticClass()));
				if (BuildingComponent != nullptr)
				{
					if (BuildingComponent->UnitDataArray.Num() < 5)
					{
						int32 NewResource = CurrentResource - UnitDataTable->Cost;
						//BuildingComponent->UnitDataArray.Emplace(GameInstance->GetUnitTable(UnitType));
						OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, NewResource);
						OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitBuildingWeightKey, 0.0f);
						OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, 0.0f);
						return EBTNodeResult::Succeeded;
					}
				}

			}
		}

		float BuildWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BuildWeightKey);
		float UnitBuildingWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitBuildingWeightKey);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BuildWeightKey, BuildWeightKey + 0.1f);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitBuildingWeightKey, UnitBuildingWeightKey + 0.1f);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Succeeded;
}

//	if (AIBuildingInfoClass == nullptr)
//	{
//		UE_LOG(LogTemp, Log, TEXT("AIBuildingClass Is NULL"));
//		return EBTNodeResult::Succeeded;
//	}
//	else
//	{
//		uint8 UnitType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::UnitTypeKey);
//		UE_LOG(LogTemp, Log, TEXT("UnitType : %d"), UnitType);
//		if (UnitType == 0)
//			return EBTNodeResult::Succeeded;
//
//		if (GameInstance != nullptr)
//			UnitDataTable = GameInstance->GetUnitTable(UnitType);
//
//
//		for (uint8 i = 0; i < AIBuildingInfoClass->AIBuildingInfo.Num(); i++)
//		{
//			if (AIBuildingInfoClass->AIBuildingInfo[i].DefaultBuilding->BuildingType == UnitDataTable->ProductionBuilding
//				&& AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo.Num() < 5)
//			{
//				int32 CurrentResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
//
//				if (UnitDataTable->Cost > CurrentResource)
//				{
//					float UnitWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitWeightKey);
//					OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, UnitWeightKey + 0.3f);
//					//처음으로 돌아가기 위해 성공 반환
//					return EBTNodeResult::Succeeded;
//				}
//				else
//				{
//					OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, 0.0f);
//					int32 NewResource = CurrentResource - UnitDataTable->Cost;
//					OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, NewResource);
//
//					//유닛 정보와 현재 대기시간 세팅
//					FWaitingUnitInfo WaitingUnitInfo;
//					WaitingUnitInfo.UnitDataTable = UnitDataTable;
//					WaitingUnitInfo.CurrentProgressTime = 0.0f;
//
//					AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo.Add(WaitingUnitInfo);
//
//					UObject* SetAIBuildingInfoClass = Cast<UObject>(AIBuildingInfoClass);
//					if (SetAIBuildingInfoClass != nullptr)
//						OwnerComp.GetBlackboardComponent()->SetValueAsObject(ACommanderAI::AIBuildingInfo, SetAIBuildingInfoClass);
//
//					return EBTNodeResult::Succeeded;
//				}
//				return EBTNodeResult::Succeeded;
//			}
//		}
//
//		float BuildWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BuildWeightKey);
//		float UnitBuildingWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitBuildingWeightKey);
//		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BuildWeightKey, BuildWeightKey + 0.1f);
//		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitBuildingWeightKey, UnitBuildingWeightKey + 0.1f);
//		
//	}
//	return EBTNodeResult::Succeeded;
//}