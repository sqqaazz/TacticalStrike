// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_RifleManDetect.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTService_RifleManDetect : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_RifleManDetect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
