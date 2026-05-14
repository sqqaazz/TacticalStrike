// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Objects/GridActor.h"
#include "BTTask_GetThreatLevel.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBTTask_GetThreatLevel : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_GetThreatLevel();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//bool CheckIsAttacking(FVector StartLocation, FVector EndLocation);
	//bool CheckIsHiding(FVector StartLocation, FVector EndLocation);

	//static void AddEdgePair(TArray<FGridEdgeHit>& Out, int X, int Y, /*const FString& Edge*/ const ETileDir& Edge);
	//TArray<FGridEdgeHit> TraceGridEdges(const FVector2D& StartWorld, const FVector2D& EndWorld, float CellSize);
	////FString ConvertEdge(const FString& Edge);
	//ETileDir ConvertEdge(const ETileDir& Edge);
	//AGridActor* GridActor;

	//void SetGridRange(int32 TileRow, int32 TileColumn, int32 Range, TFunction<void(int32, int32)> SetMoveTile);

	//void GetThreatLevel(int32 TileRow, int32 TileColumn);
	//void SetMoveTile_NoEnemy();

	//UPROPERTY()
	//TArray<FIntPoint> MoveCandidatesArr;

	//UPROPERTY()
	//UTacticalStrikeGameInstance* GameInstance;

	//UPROPERTY()
	//class ADefaultUnit* DefaultUnit;
};

