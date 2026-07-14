// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FinishAIHavior.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_FinishAIHavior : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTask_FinishAIHavior();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
