// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CommandAI_OperateCombatAI.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_CommandAI_OperateCombatAI : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTask_CommandAI_OperateCombatAI();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void FinishCombatAIhaviorTask();

	class UBehaviorTreeComponent* CurOwnerComp;
};
