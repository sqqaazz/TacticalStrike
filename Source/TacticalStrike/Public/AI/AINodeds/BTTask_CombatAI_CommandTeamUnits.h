// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CombatAI_CommandTeamUnits.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_CombatAI_CommandTeamUnits : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_CombatAI_CommandTeamUnits();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void FinishUnithaviorTask();

	class UBehaviorTreeComponent* CurOwnerComp;
};
