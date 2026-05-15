// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Units/DefaultUnit/BTTask_DefaultUnit_MoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Objects/GridActor.h"
#include "Components/GridTileActor.h"

UBTTask_DefaultUnit_MoveToTarget::UBTTask_DefaultUnit_MoveToTarget()
{
	NodeName = TEXT("DefaultUnit_MoveToTarget");
}

EBTNodeResult::Type UBTTask_DefaultUnit_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	CurOwnerComp = &OwnerComp;

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	DefaultUnit = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	if (GameInstance == nullptr || GridActor == nullptr || DefaultUnit == nullptr)
		return EBTNodeResult::Failed;

	UnitDataInfo = GameInstance->GetUnitTable(static_cast<int32>(DefaultUnit->ObjectInfo.ObjectType));
	DefaultUnit->MovingStopDelegate.AddUObject(this, &UBTTask_DefaultUnit_MoveToTarget::EndMove);

	//FVector MovingLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ADefaultUnitAI::MovingPosKey);
	UnitTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::TargetKey));
	if (UnitTarget == nullptr)
		return EBTNodeResult::Failed;
	FVector MovingLocation = UnitTarget->GetActorLocation();
	FVector CurrentLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

	int32 GoalTileRow = int32(FMath::Floor(MovingLocation.X / 100));
	int32 GoalTileColumn = int32(FMath::Floor(MovingLocation.Y / 100));
	int32 CurTileRow = int32(FMath::Floor(CurrentLocation.X / 100));
	int32 CurTileColumn = int32(FMath::Floor(CurrentLocation.Y / 100));

	TArray<FIntPoint> TargetPath = FindPath(FIntPoint(CurTileRow, CurTileColumn), FIntPoint(GoalTileRow, GoalTileColumn));
	//UE_LOG(LogTemp, Log, TEXT("Location: [%d, %d]"), GoalTileRow, GoalTileColumn);

	//for (int32 i = 0; i < TargetPath.Num(); i++)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Path: [%d, %d]"), TargetPath[i].X, TargetPath[i].Y);
	//}
	//OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::MainTeamAIKey);
	StartMove(TargetPath);

	return EBTNodeResult::InProgress;
}

float UBTTask_DefaultUnit_MoveToTarget::GetCost(ETileDir PrevDir, ETileDir NextDir)
{
	if (PrevDir == ETileDir::None || PrevDir == NextDir)
		return 1.0f;
	else
		return 1.0f + 100.0f;
}

float UBTTask_DefaultUnit_MoveToTarget::Heuristic(int32 X, int32 Y, int32 dX, int32 dY)
{
	return FMath::Abs(dX - X) + FMath::Abs(dY - Y);
}

FString UBTTask_DefaultUnit_MoveToTarget::MakeNodeKey(int32 X, int32 Y, ETileDir TileDir)
{
	return FString::Printf(TEXT("%d_%d_%d"), X, Y, (int32)TileDir);
}

TArray<FIntPoint> UBTTask_DefaultUnit_MoveToTarget::BuildPath(int32 GoalIndex)
{
	TArray<FIntPoint> Path;

	int32 CurrentIndex = GoalIndex;

	while (CurrentIndex != INDEX_NONE)
	{
		FGridNode& Node = GridNodes[CurrentIndex];

		Path.Add(FIntPoint(Node.X, Node.Y));
		CurrentIndex = Node.ParentIndex;
	}

	Algo::Reverse(Path);
	return Path;
}


TArray<FIntPoint> UBTTask_DefaultUnit_MoveToTarget::FindPath(FIntPoint StartGrid, FIntPoint GoalGrid)
{
	TArray<FIntPoint> Directions = {{0,1}, {0,-1}, {-1,0}, {1,0}};

	TArray<ETileDir> DirEnum = {ETileDir::Top, ETileDir::Bottom, ETileDir::Left, ETileDir::Right};

	TArray<int32> OpenSet;

	FGridNode StartNode(StartGrid.X, StartGrid.Y, ETileDir::None, 0.0f, Heuristic(StartGrid.X, StartGrid.Y, GoalGrid.X, GoalGrid.Y), INDEX_NONE);
	int32 StartIndex = GridNodes.Add(StartNode);
	OpenSet.Add(StartIndex);

	while (OpenSet.Num() > 0)
	{
		OpenSet.Sort([this](int32 A, int32 B)
		{
			return GridNodes[A].F < GridNodes[B].F;
		});
		
		int32 CurrentIndex = OpenSet[0];
		OpenSet.RemoveAt(0);

		FGridNode& CurrentNode = GridNodes[CurrentIndex];

		//if (CurrentNode.X == GoalGrid.X && CurrentNode.Y == GoalGrid.Y)
		//{
		//	return BuildPath(CurrentIndex);
		//}


		for (int32 i = 0; i < 4; i++)
		{
			int32 NX = CurrentNode.X + Directions[i].X;
			int32 NY = CurrentNode.Y + Directions[i].Y;
			ETileDir NDir = DirEnum[i];


			if (!GridActor->TileCheck(NX, NY))
				continue;

			if (GridActor->GridTileArr[NX][NY]->ObjectInfo.ObjectActor == UnitTarget)
			{
				return BuildPath(CurrentIndex);
			}

			if (!(NX == GoalGrid.X && NY == GoalGrid.Y))
			{
				if (GridActor->GridTileArr[NX][NY]->ObjectInfo.ObjectActor != nullptr)
					continue;
			}

			float NewG = CurrentNode.G + GetCost(CurrentNode.TileDir, NDir);

			FString Key = MakeNodeKey(NX, NY, NDir);

			if (!BestCost.Contains(Key) || NewG < BestCost[Key])
			{
				BestCost.Add(Key, NewG);

				FGridNode NextNode;
				NextNode.X = NX;
				NextNode.Y = NY;
				NextNode.TileDir = NDir;
				NextNode.G = NewG;
				NextNode.F = NewG + Heuristic(NX, NY, GoalGrid.X, GoalGrid.Y);
				NextNode.ParentIndex = CurrentIndex;

				int32 NewIndex = GridNodes.Add(NextNode);
				OpenSet.Add(NewIndex);
			}
		}
	}
	return {};
}


void UBTTask_DefaultUnit_MoveToTarget::StartMove(TArray<FIntPoint> Path)
{
	GridActor->RemoveTile_Unit(Path[0]);
	GridActor->SetTile_Unit(Path[Path.Num() - 1], DefaultUnit);
	DefaultUnit->StartMoving(Path);
}

void UBTTask_DefaultUnit_MoveToTarget::EndMove()
{
	int32 ActionCountKey = CurOwnerComp->GetBlackboardComponent()->GetValueAsInt(ADefaultUnitAI::ActionCountKey);
	ActionCountKey--;
	CurOwnerComp->GetBlackboardComponent()->SetValueAsInt(ADefaultUnitAI::ActionCountKey, ActionCountKey);
	FinishLatentTask(*CurOwnerComp, EBTNodeResult::Succeeded);
}