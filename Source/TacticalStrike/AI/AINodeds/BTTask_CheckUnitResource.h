// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DataTables/UnitDataTables.h"
#include "BTTask_CheckUnitResource.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_CheckUnitResource : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_CheckUnitResource();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class UTacticalStrikeGameInstance* GameInstance;
	FUnitTableRow* UnitDataTable;
};
