// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetBattleFrontWeight.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_SetBattleFrontWeight : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetBattleFrontWeight();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


private:
	TArray<AActor*> DefaultUnitArr;
	TArray<class ADefaultUnit*> RedTeamUnitArr;

	TArray<AActor*> TampleArr;

	//float TampleLocationAvg;
	float BattleFrontAvg;
};
