// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DataTables/BuildingDataTables.h"
#include "Objects/GridActor.h"
#include "Components/GridTileActor.h"
#include "BTTask_SpawnBuilding.generated.h"



UCLASS()
class TACTICALSTRIKE_API UBTTask_SpawnBuilding : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTask_SpawnBuilding();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


public:
	AGridActor* GridActor;


private:
	//class UAIBuildingInfoClass* AIBuildingInfoClass;
	class UTacticalStrikeGameInstance* GameInstance;
	//FBuildingTableRow* BuildingDataTable;
	struct FBuildingTableRow* BuildingDataInfo;
	class ACommanderAI* CommanderAI;

	TArray<class AGridTileActor*> AIEnergyTileArr;
	void SpawnGridBuilding(int32 BuildingKey);

	//void SpawnBuilding();
};
