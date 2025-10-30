// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_RifleMan_Distance.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTService_RifleMan_Distance : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_RifleMan_Distance();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
