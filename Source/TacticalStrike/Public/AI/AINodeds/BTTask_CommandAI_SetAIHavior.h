// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI/AIController/CommanderAI.h"
//#include "DataTables/UnitDataTables.h"
#include "BTTask_CommandAI_SetAIHavior.generated.h"

USTRUCT(BlueprintType)
struct FHaviorWeight
{
	GENERATED_BODY()

	UPROPERTY()
	float HaviorWeight;

	UPROPERTY()
	EAIBehaviorCode HaviorCode;
};

UCLASS()
class TACTICALSTRIKE_API UBTTask_CommandAI_SetAIHavior : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_CommandAI_SetAIHavior();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
	float TotalWeight;

	bool CheckPreviousFailedHavior(UBehaviorTreeComponent& OwnerComp);

	float GetPreviousHaviorWeight(UBehaviorTreeComponent& OwnerComp, float RemainWeight, TArray<FHaviorWeight>& HaviorWeightArr);
	float GetSpawnUnitWeight(TArray<class AActor*> SightEnemyArr, TArray<class ADefaultUnit*> TeamUnitArr, float RemainWeight, TArray<FHaviorWeight>& HaviorWeightArr);

	float GetResearchWeight(float RemainWeight, TArray<FHaviorWeight>& HaviorWeightArr);
	float GetResourceWeight(float RemainWeight, TArray<FHaviorWeight>& HaviorWeightArr);

	UPROPERTY()
	class UTacticalStrikeGameInstance* GameInstance;

	//struct FUnitTableRow* UnitDataInfo;
};
