// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DataTables/UnitDataTables.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "BTTask_DefaultUnit_MoveToTarget.generated.h"

USTRUCT(BlueprintType)
struct FGridNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileDir TileDir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float G;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float F;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ParentIndex;

	FGridNode()
		: X(0), Y(0), TileDir(ETileDir::None), G(0), F(0), ParentIndex(INDEX_NONE)
	{}

	FGridNode(int32 InX, int32 InY, ETileDir InTileDir, float InG, float InF, int32 InParentIndex)
		: X(InX), Y(InY), TileDir(InTileDir), G(InG), F(InF), ParentIndex(InParentIndex)
		{}
};

UCLASS()
class TACTICALSTRIKE_API UBTTask_DefaultUnit_MoveToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_DefaultUnit_MoveToTarget();

	UPROPERTY()
	class AGridActor* GridActor;
	UPROPERTY()
	class ADefaultUnit* DefaultUnit;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UBehaviorTreeComponent* CurOwnerComp;
private:
	UPROPERTY()
	class UTacticalStrikeGameInstance* GameInstance;

	FUnitTableRow* UnitDataInfo;

	UPROPERTY()
	TArray<FGridNode> GridNodes;

	float GetCost(ETileDir PrevDir, ETileDir NextDir);
	float Heuristic(int32 X, int32 Y, int32 dX, int32 dY);

	TArray<FIntPoint> BuildPath(int32 GoalIndex);

	void StartMove(TArray<FIntPoint> Path);
	UFUNCTION()
	void EndMove();

	UPROPERTY()
	TMap<FString, float> BestCost;

	FString MakeNodeKey(int32 X, int32 Y, ETileDir TileDir);

	UPROPERTY()
	AActor* UnitTarget;
public:
	TArray<FIntPoint> FindPath(FIntPoint StartGrid, FIntPoint GoalGrid);

};
