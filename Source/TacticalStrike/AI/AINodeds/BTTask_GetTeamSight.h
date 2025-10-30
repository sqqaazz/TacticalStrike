// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "BTTask_GetTeamSight.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_GetTeamSight : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_GetTeamSight();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	TArray<ADefaultUnit*> TeamUnitArr;
	
};
