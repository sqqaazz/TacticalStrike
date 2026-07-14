// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "DataTables/UnitDataTables.h"
#include "DataTables/UpgradeDataTables.h"
#include "AIBuildingInfoClass.generated.h"
/**
 * 
 */

USTRUCT()
struct FWaitingUnitInfo
{
	GENERATED_BODY()

public:
	FUnitTableRow* UnitDataTable;
	float CurrentProgressTime;
};

USTRUCT()
struct FResearchWaitingInfo
{
	GENERATED_BODY()

public:
	FUpgradeTableRow* UpgradeDataTable;
	float CurrentProgressTime;
};


USTRUCT()
struct FAIBuildingInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	ADefaultBuilding* DefaultBuilding;
	UPROPERTY()
	TArray<FWaitingUnitInfo> WaitingUnitInfo;
	UPROPERTY()
	TArray<FResearchWaitingInfo> ResearchWaitingInfo;
};

UCLASS()
class TACTICALSTRIKE_API UAIBuildingInfoClass : public UObject
{
	GENERATED_BODY()

public:
	TArray<FAIBuildingInfo> AIBuildingInfo;
};


//class TACTICALSTRIKE_API AIBuildingInfoClass
//{
//public:
//	AIBuildingInfoClass();
//	~AIBuildingInfoClass();
//};
