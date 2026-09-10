// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_SpawnUnit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
//#include "AIBuildingInfoClass.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/BuildingClickableComponent.h"
#include "DataTables/UnitDataTables.h"

UBTTask_SpawnUnit::UBTTask_SpawnUnit()
{
	NodeName = TEXT("SpawnUnit");
}

EBTNodeResult::Type UBTTask_SpawnUnit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));

	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());
	int32 AIResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
	int8 AIHaviorSequenceIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey);
	FHaviorStateSequence HaviorStateSequenceQueue = CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex];
	uint8 UnitTypeKey = static_cast<uint8>(HaviorStateSequenceQueue.SpawnObjectType);
	UnitDataInfo = GameInstance->GetUnitTable(static_cast<int32>(UnitTypeKey));

	if (!HaviorStateSequenceQueue.SpawnBuilding.IsValid() || CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState == EAIBehaviorState::Failed_Lack_Building)
	{
		//OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Waited_Building));
		CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState = EAIBehaviorState::Failed_Lack_Building;
		return EBTNodeResult::Succeeded;
	}
	//UE_LOG(LogTemp, Log, TEXT("Resource: %d"), AIResource);
	if (AIResource < UnitDataInfo->Cost)
	{
		//OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Failed_Lack_Resource));
		CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState = EAIBehaviorState::Failed_Lack_Resource;
		return EBTNodeResult::Succeeded;
	}

	UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
		(HaviorStateSequenceQueue.SpawnBuilding->GetComponentByClass(UBuildingClickableComponent::StaticClass()));

	FObjectInfo UnitObjectInfo(static_cast<int32>(UnitTypeKey), UnitDataInfo->MaxHP, EObjectState::DeActivated, UnitDataInfo->BuildTime, 0, EObjectOwner::Red, 0, nullptr);
	BuildingComponent->UnitDataArray.Emplace(UnitObjectInfo);
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, AIResource - UnitDataInfo->Cost);

	CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState = EAIBehaviorState::Successed;


	//uint8 UnitTypeKey = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::UnitTypeKey);
	//bIsProductionBuildingDeActivated = false;
	//AIEnergyTileArr = GridActor->CheckAIEnegyTile();
	//SpawnUnit(UnitTypeKey, OwnerComp);

	return EBTNodeResult::Succeeded;
}

//void UBTTask_SpawnUnit::SpawnUnit(uint8 UnitKey, UBehaviorTreeComponent& OwnerComp)
//{
//	UnitDataInfo = GameInstance->GetUnitTable(static_cast<int32>(UnitKey));
//	if (UnitDataInfo == nullptr)
//		return;
//
//	int32 AIResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
//	if (AIResource < UnitDataInfo->Cost)
//	{
//		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Failed_Lack_Resource));
//		return;
//	}
//
//	for (auto EnergyTile : AIEnergyTileArr)
//	{
//		if (EnergyTile->ObjectInfo.ObjectState == EObjectState::Activated && EnergyTile->ObjectInfo.ObjectType == uint8(UnitDataInfo->ProductionBuilding))
//		{
//			
//			UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
//				(EnergyTile->ObjectInfo.ObjectActor->GetComponentByClass(UBuildingClickableComponent::StaticClass()));
//			if (BuildingComponent != nullptr)
//			{
//				if (BuildingComponent->UnitDataArray.Num() < 5)
//				{
//					ADefaultBuilding* SpawnBuilding = Cast<ADefaultBuilding>(EnergyTile->ObjectInfo.ObjectActor);
//					if (SpawnBuilding != nullptr)
//					{
//						SpawnBuilding->ObjectInfo.ObjectState = EObjectState::BuildWaited;
//						SpawnBuilding->ObjectState = EObjectState::BuildWaited;
//
//						FObjectInfo UnitObjectInfo(static_cast<int32>(UnitKey), UnitDataInfo->MaxHP, EObjectState::DeActivated, UnitDataInfo->BuildTime, 0, EObjectOwner::Red, 0, nullptr);
//
//						BuildingComponent->UnitDataArray.Emplace(UnitObjectInfo);
//
//						FUnitTableRow* UnitDataTable = GameInstance->GetUnitTable(UnitKey);
//						int32 ResourceKey = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
//						OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, ResourceKey - UnitDataTable->Cost);
//						OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Successed));
//						return;
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//		}
//		else if (EnergyTile->ObjectInfo.ObjectState == EObjectState::DeActivated && EnergyTile->ObjectInfo.ObjectType == uint8(UnitDataInfo->ProductionBuilding))
//		{
//			
//			bIsProductionBuildingDeActivated = true;
//		}
//	}
//	if (bIsProductionBuildingDeActivated)
//	{
//		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Waited_Building));
//	}
//	else
//	{
//		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::BuildingTypeKey, UnitDataInfo->ProductionBuilding);
//		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Failed_Lack_Building));
//	}
//}

//EBTNodeResult::Type UBTTask_SpawnUnit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
//	//UAIBuildingInfoClass* AIBuildingInfoClass = Cast<UAIBuildingInfoClass>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACommanderAI::AIBuildingInfo));
//	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//
//	uint8 UnitType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::UnitTypeKey);
//	if (GameInstance != nullptr)
//		UnitDataTable = GameInstance->GetUnitTable(UnitType);
//	if (UnitType == 0)
//		return EBTNodeResult::Succeeded;
//
//	int32 CurrentResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
//	if (UnitDataTable->Cost > CurrentResource)
//	{
//		float UnitWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitWeightKey);
//		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, UnitWeightKey + 0.1f);
//		//처음으로 돌아가기 위해 성공 반환
//		return EBTNodeResult::Succeeded;
//	}
//	else
//	{
//		TArray<AActor*> BuildingArray;
//		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultBuilding::StaticClass(), BuildingArray);
//
//		for (uint8 i = 0; i < BuildingArray.Num(); i++)
//		{
//			ADefaultBuilding* SpawnBuilding = Cast<ADefaultBuilding>(BuildingArray[i]);
//			if (SpawnBuilding != nullptr && SpawnBuilding->ActorHasTag("RedTeamBuildings") 
//				&& SpawnBuilding->BuildingType == UnitDataTable->ProductionBuilding)
//			{
//				UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
//					(SpawnBuilding->GetComponentByClass(UBuildingClickableComponent::StaticClass()));
//				if (BuildingComponent != nullptr)
//				{
//					if (BuildingComponent->UnitDataArray.Num() < 5)
//					{
//						int32 NewResource = CurrentResource - UnitDataTable->Cost;
//						//BuildingComponent->UnitDataArray.Emplace(GameInstance->GetUnitTable(UnitType));
//						OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, NewResource);
//						OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitBuildingWeightKey, 0.0f);
//						OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, 0.0f);
//						return EBTNodeResult::Succeeded;
//					}
//				}
//
//			}
//		}
//
//		float BuildWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BuildWeightKey);
//		float UnitBuildingWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitBuildingWeightKey);
//		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BuildWeightKey, BuildWeightKey + 0.1f);
//		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitBuildingWeightKey, UnitBuildingWeightKey + 0.1f);
//
//		return EBTNodeResult::Succeeded;
//	}
//	return EBTNodeResult::Succeeded;
//}

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