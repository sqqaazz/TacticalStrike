// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpawnResourceComponent.h"
#include "Objects/GridActor.h"
#include "Characters/DefaultSpawningActor.h"
#include "Kismet/GameplayStatics.h"
#include "Algo/RandomShuffle.h"

USpawnResourceComponent::USpawnResourceComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	SpawnResourceCount = 100;
    Radius = 5;
}


// Called when the game starts
void USpawnResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	GridActor = Cast<AGridActor>(GetOwner());
	DefaultSpawningActor = Cast<ADefaultSpawningActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ADefaultSpawningActor::StaticClass()));

	Rows = GridActor->Rows / 2;
	Columns = GridActor->Columns;

    ArrangementResourceField();
    SpawnResource();
}


void USpawnResourceComponent::ArrangementResourceField()
{
    MakeBlockedTile_BuildingTile();

	while (SpawnResourceCount > 0)
	{
		int32 Count = FMath::RandRange(12, 15);

        if (SpawnResourceCount < Count)
            Count = SpawnResourceCount;

		MakeResourceCluster(Count);
		SpawnResourceCount -= Count;

        MakeBlockedTile();
	}
}

void USpawnResourceComponent::SpawnResource()
{
    //UE_LOG(LogTemp, Log, TEXT("ResourceNum: %d"), Occupied.Num());
    for (const FIntPoint Tile : Occupied)
    {
        DefaultSpawningActor->SpawnBuilding(ESpawnBuilding::Crystal, FVector(Tile.X * 100 + 50.0f, Tile.Y * 100 + 50.0f, 10.0f));

        DefaultSpawningActor->SpawnBuilding(ESpawnBuilding::Crystal, FVector((99 - Tile.X) * 100 + 50.0f, (100 - Tile.Y) * 100 + 50.0f, 10.0f));
    }
}

void USpawnResourceComponent::MakeResourceCluster(int32 ClusterSize)
{
	FIntPoint ClusterCenter = GetClusterCenter();

	if (!TileCheck(ClusterCenter))
		return;

    TQueue<FIntPoint> Queue;
    TSet<FIntPoint> Visited;

    Queue.Enqueue(ClusterCenter);
    Visited.Add(ClusterCenter);

    while (!Queue.IsEmpty() && ClusterSize > 0)
    {
        FIntPoint CurrentTile;
        Queue.Dequeue(CurrentTile);

        if (Occupied.Contains(CurrentTile))
            continue;

        Occupied.Add(CurrentTile);
        ClusterSize--;

        TArray<FIntPoint> NeighborsTile =
        {
            { CurrentTile.X + 1, CurrentTile.Y },
            { CurrentTile.X + 1, CurrentTile.Y + 1 },
            { CurrentTile.X - 1, CurrentTile.Y },
            { CurrentTile.X - 1, CurrentTile.Y + 1},
            { CurrentTile.X, CurrentTile.Y + 1 },
            { CurrentTile.X + 1, CurrentTile.Y - 1},
            { CurrentTile.X, CurrentTile.Y - 1 },
            { CurrentTile.X - 1, CurrentTile.Y - 1}
        };

        Algo::RandomShuffle(NeighborsTile);

        for (const FIntPoint& NextTile : NeighborsTile)
        {
            if (!TileCheck(NextTile))
                continue;

            if (Visited.Contains(NextTile))
                continue;

            if (Blocked.Contains(NextTile))
                continue;

            //Visited.Add(NextTile);
           // Queue.Enqueue(NextTile);

            if (FMath::FRand() < 0.4f)
            {
                Visited.Add(NextTile);
                Queue.Enqueue(NextTile);
            }
        }
    }
}

void USpawnResourceComponent::MakeBlockedTile()
{
    for (const FIntPoint Tile : Occupied)
    {
        for (int32 i = -Radius; i <= Radius; i++)
        {
            for (int32 j = -Radius; j <= Radius; j++)
            {
                FIntPoint Pos = (Tile.X + i, Tile.Y + j);

                if (!TileCheck(Pos))
                    continue;

                Blocked.Add(Pos);
            }
        }
    }
}

void USpawnResourceComponent::MakeBlockedTile_BuildingTile()
{
    for (int32 i = 0; i < GridActor->GridTileArr.Num() / 2; i++)
    {
        for (const UGridTileActor* GridTile : GridActor->GridTileArr[i].GridTileColumn)
        {
            if (GridTile->ObjectInfo.ObjectActor != nullptr)
            {
                for (int32 j = -Radius * 2; j <= Radius * 2; j++)
                {
                    for (int32 k = -Radius * 2; k <= Radius * 2; k++)
                    {
                        FIntPoint Pos = (GridTile->Rows + j, GridTile->Columns + k);

                        if (!TileCheck(Pos))
                            continue;

                        Blocked.Add(Pos);
                    }
                }
            }
        }
    }

}

FIntPoint USpawnResourceComponent::GetClusterCenter()
{
	int32 MaxTry = 500;

	for (int32 i = 0; i < MaxTry; i++)
	{
		FIntPoint CandidateTile(FMath::RandRange(0, Rows - 1),FMath::RandRange(0, Columns - 1));

		if (!Blocked.Contains(CandidateTile))
		{
			return CandidateTile;
		}
	}
	return FIntPoint(-1, -1);
}

bool USpawnResourceComponent::TileCheck(FIntPoint CheckTile)
{
	if (CheckTile.X >= 0 && CheckTile.X < Rows && CheckTile.Y >= 0 && CheckTile.Y < Columns)
		return true;
	else
		return false;
}

// Called every frame
//void USpawnResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

