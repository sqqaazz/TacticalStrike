// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DataTables/UnitDataTables.h"
#include "DataTables/UpgradeDataTables.h"
#include "BTTask_SetBuildingType.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_SetBuildingType : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetBuildingType();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class UTacticalStrikeGameInstance* GameInstance;

	UPROPERTY()
	TArray<float> BuildingWeightArr;
	FUnitTableRow* UnitDataTable;
	FUpgradeTableRow* UpgradeDataTable;
};
