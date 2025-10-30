// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetAIResource.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_SetAIResource : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetAIResource();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	TArray<AActor*> CrystalArray;
};
