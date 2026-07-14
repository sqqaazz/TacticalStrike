// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DefaultUnit_StartUnitTurn.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_DefaultUnit_StartUnitTurn : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_DefaultUnit_StartUnitTurn();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
