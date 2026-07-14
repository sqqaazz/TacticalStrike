// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TeamCombatAI_StartTurn.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_TeamCombatAI_StartTurn : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TeamCombatAI_StartTurn();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void StartTurn_Player();
	void StartTurn_AI();
};
