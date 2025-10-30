// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DefaultUnitAttack.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_DefaultUnitAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_DefaultUnitAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	bool IsAttacking = false;
};
