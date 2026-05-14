// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnBuilding.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpawnBuildingComponent.h"
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
	int TempBuildingTypeKey = static_cast<int32>(ESpawnBuilding::Barracks);

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::BuildingTypeKey, TempBuildingTypeKey);

	int32 BuildingTypeKey = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::BuildingTypeKey);

	SpawnGridBuilding(BuildingTypeKey);

	return EBTNodeResult::Succeeded;
}

void UBTTask_SpawnBuilding::SpawnGridBuilding(int32 BuildingKey)
{
	BuildingDataInfo = GameInstance->GetBuildingTable(static_cast<int32>(BuildingKey));
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
			CommanderAI->SpawnBuildingComponent->AI_SpawnBuildings_Grid(FIntPoint(EnergyTile->Rows, EnergyTile->Columns), SpawnBuilding);
			return;
		}
	}
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