// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DataTables/UnitDataTables.h"
#include "BTDecorator_Default_Range.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTDecorator_Default_Range : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_Default_Range();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
};
