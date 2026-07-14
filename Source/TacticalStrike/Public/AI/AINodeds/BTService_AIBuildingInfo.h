// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DataTables/UnitDataTables.h"
#include "DataTables/UpgradeDataTables.h"
#include "BTService_AIBuildingInfo.generated.h"

/**
 * 
 */
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIBehaviorDelegate, uint8, ObjectType);


UCLASS()
class TACTICALSTRIKE_API UBTService_AIBuildingInfo : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_AIBuildingInfo();

	/*UPROPERTY()
	FAIBehaviorDelegate AIBehaviorDelegate;*/

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	class UTacticalStrikeGameInstance* GameInstance;
	FUnitTableRow* UnitDataTable;
	FUpgradeTableRow* UpgradeDataTable;
};
