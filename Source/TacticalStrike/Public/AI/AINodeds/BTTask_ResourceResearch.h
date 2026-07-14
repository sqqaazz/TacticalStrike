// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DataTables/UpgradeDataTables.h"
#include "BTTask_ResourceResearch.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_ResourceResearch : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ResourceResearch();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class UTacticalStrikeGameInstance* GameInstance;

	FUpgradeTableRow* UpgradeDataTable;
};
