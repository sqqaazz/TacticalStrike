// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_SpawnBuilding.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpawnBuildingComponent.h"
#include "DataTables/BuildingDataTables.h"
//#include "AIBuildingInfoClass.h"

UBTTask_SpawnBuilding::UBTTask_SpawnBuilding()
{
	NodeName = TEXT("SpawnBuilding");
}

EBTNodeResult::Type UBTTask_SpawnBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());

	if (GameInstance == nullptr || GridActor == nullptr)
		return EBTNodeResult::Failed;

	AIEnergyTileArr = GridActor->CheckAIEnegyTile();
	//UE_LOG(LogTemp, Log, TEXT("EnegyTile: %d"), AIEnergyTileArr.Num());
	//int TempBuildingTypeKey = static_cast<int32>(ESpawnBuilding::Barracks);
	//OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::BuildingTypeKey, TempBuildingTypeKey);

	int32 BuildingTypeKey = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::BuildingTypeKey);

	if (SpawnGridBuilding(BuildingTypeKey, OwnerComp))
	{
		int8 AIHaviorSequenceIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey);
		FHaviorStateSequence HaviorStateSequenceQueue = CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex];

		//if (HaviorStateSequenceQueue.HaviorCode == EAIBehaviorCode::Havior_SpawnBuilding_Unit && HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Waited_Building)
		//{
		//	//CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState == EAIBehaviorState::Waited_SpawnUnit;
		//}
	}
	else
	{

	}

	return EBTNodeResult::Succeeded;
}

bool UBTTask_SpawnBuilding::SpawnGridBuilding(int32 BuildingKey, UBehaviorTreeComponent& OwnerComp)
{
	BuildingDataInfo = GameInstance->GetBuildingTable(static_cast<int32>(BuildingKey));

	int32 AIResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
	if (AIResource < BuildingDataInfo->Cost)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Failed_Lack_Resource));
		return false;
	}

	ESpawnBuilding SpawnBuilding = static_cast<ESpawnBuilding>(BuildingKey);
	for (auto EnergyTile : AIEnergyTileArr)
	{
		//if (EnergyTile->ObjectInfo.ObjectActor != nullptr)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("Name: %s"), *EnergyTile->ObjectInfo.ObjectActor->GetName());
		//}

		FIntPoint BuildingStartGrid = GridActor->GetStartGridTile(EnergyTile->Rows, EnergyTile->Columns, BuildingDataInfo->GridSizeX, BuildingDataInfo->GridSizeY, EObjectOwner::Red);
		bool IsEnableBuilding = GridActor->CheckEnableBuilding(BuildingStartGrid, BuildingDataInfo->GridSizeX, BuildingDataInfo->GridSizeY);
		//UE_LOG(LogTemp, Log, TEXT("Grid: [%d, %d]"), BuildingStartGrid.X, BuildingStartGrid.Y);
		if (IsEnableBuilding)
		{
			//CommanderAI->SpawnBuildingComponent->AI_SpawnBuildings_Grid(FIntPoint(EnergyTile->Rows, EnergyTile->Columns), SpawnBuilding);
			CommanderAI->AIBuildingsArr.Add
			(CommanderAI->SpawnBuildingComponent->AI_SpawnBuildings_Grid(FIntPoint(EnergyTile->Rows, EnergyTile->Columns), SpawnBuilding));

			FBuildingTableRow* BuildingDataTable = GameInstance->GetBuildingTable(BuildingKey);
			int32 ResourceKey = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, ResourceKey - BuildingDataTable->Cost);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Successed));

			return true;
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::Failed_Lack_Territory));

	return false;
}

//EBTNodeResult::Type UBTTask_SpawnBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
//
//	//AIBuildingInfoClass = Cast<UAIBuildingInfoClass>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACommanderAI::AIBuildingInfo));
//	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//
//		uint8 BuildingType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::BuildingTypeKey);
//		int32 CurrentResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
//
//		if (BuildingType == 0)
//			return EBTNodeResult::Succeeded;
//
//		if (GameInstance != nullptr)
//			BuildingDataTable = GameInstance->GetBuildingTable(BuildingType);
//
//		if (CurrentResource > BuildingDataTable->Cost)
//		{
//			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, CurrentResource - BuildingDataTable->Cost);
//			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BuildWeightKey, 0.0f);
//
//			if (BuildingType < 150)
//				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitBuildingWeightKey, 0.0f);
//			else if (BuildingType >= 150)
//				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::ResourceBuildingWeightKey, 0.0f);
//
//			ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());
//			if (CommanderAI != nullptr)
//				CommanderAI->AIBehavior(BuildingType);
//
//			return EBTNodeResult::Succeeded;
//		}
//		else
//		{
//			float BuildWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BuildWeightKey);
//			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BuildWeightKey, BuildWeightKey + 0.1f);
//			return EBTNodeResult::Succeeded;
//		}
//
//}