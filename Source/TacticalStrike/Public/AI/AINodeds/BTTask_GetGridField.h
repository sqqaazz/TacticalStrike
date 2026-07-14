// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetGridField.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_GetGridField : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GetGridField();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
};
