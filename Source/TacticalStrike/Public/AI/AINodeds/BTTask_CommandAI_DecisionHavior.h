// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CommandAI_DecisionHavior.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_CommandAI_DecisionHavior : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_CommandAI_DecisionHavior();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
