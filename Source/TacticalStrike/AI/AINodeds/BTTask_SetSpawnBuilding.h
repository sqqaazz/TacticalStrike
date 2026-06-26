// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Objects/GridActor.h"
#include "Components/GridTileActor.h"
#include "BTTask_SetSpawnBuilding.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_SetSpawnBuilding : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetSpawnBuilding();

	AGridActor* GridActor;
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
