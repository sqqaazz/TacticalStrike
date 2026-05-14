// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DataTables/UnitDataTables.h"
#include "Objects/GridActor.h"
#include "Components/GridTileActor.h"
#include "BTTask_SpawnUnit.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_SpawnUnit : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SpawnUnit();

	AGridActor* GridActor;
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	

private:
	class UTacticalStrikeGameInstance* GameInstance;
	FUnitTableRow* UnitDataInfo;

	TArray<class AGridTileActor*> AIEnergyTileArr;

	void SpawnUnit(uint8 UnitKey);
};
