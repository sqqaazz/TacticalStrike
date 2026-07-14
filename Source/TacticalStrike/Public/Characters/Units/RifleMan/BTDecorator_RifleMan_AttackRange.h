// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_RifleMan_AttackRange.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTDecorator_RifleMan_AttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_RifleMan_AttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
