// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/GridActor.h"
#include "ProceduralMeshComponent.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "GameMode/TacticalStrikeGameStateBase.h"

//#include "Characters/Units/DefaultUnit/DefaultUnit.h"

// Sets default values
AGridActor::AGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProceduralMesh_Lines = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GridProceduralMesh_Lines"));
	ProceduralMesh_Squares = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GridProceduralMesh_Squares"));
	GridCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridCollisionMesh"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MATERIALINSTANCE(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Grid.MI_Grid'"));
	if (MATERIALINSTANCE.Succeeded())
		GridMaterialInstance = MATERIALINSTANCE.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> MATERIAL(TEXT("/Script/Engine.Material'/Game/Material/M_SquareGrid.M_SquareGrid'"));
	if (MATERIAL.Succeeded())
		SquareMaterial = MATERIAL.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GRIDCOLLISIONMESH(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (GRIDCOLLISIONMESH.Succeeded())
		GridCollisionMesh->SetStaticMesh(GRIDCOLLISIONMESH.Object);

	Rows = 100;
	Columns = 100;
	TileSize = 100.0f;
	LineThiccness = 5.0f;
	LineOpacity = 0.5f;
	SquareOpacity = 0.6f;
	SquareOpacity_Transparent = 0.0f;

	LineColor = FLinearColor::Gray;
	//SquareColor_Enable = FLinearColor::Green;
	//SquareColor_Disable = FLinearColor::Red;
	//SquareColor_Energy = FLinearColor::Yellow;


	//ProceduralMesh_Squares->SetCollisionProfileName(TEXT("Grid"));
	//ProceduralMesh_Lines->SetCollisionProfileName(TEXT("Grid"));
	GridCollisionMesh->SetCollisionProfileName(TEXT("Grid"));
	GridCollisionMesh->SetRelativeScale3D(FVector(10.0f, 10.0f, 0.1f));
	GridCollisionMesh->SetVisibility(false);

}

void AGridActor::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	GridMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(GridMaterialInstance, this);
	//GridMaterialInstanceDynamic_Lines = CreateMaterialInstance(LineColor, LineOpacity);
	//GridMaterialInstanceDynamic_Squares_Enable = CreateMaterialInstance(SquareColor_Enable, SquareOpacity);
	//GridMaterialInstanceDynamic_Squares_Disable = CreateMaterialInstance(SquareColor_Disable, SquareOpacity);
	//GridMaterialInstanceDynamic_Squares_Energy = CreateMaterialInstance(SquareColor_Energy, SquareOpacity);

	GridTileArr.SetNum(Rows);

	for (int32 i = 0; i < Rows; i++)
	{
		for (int32 j = 0; j < Columns; j++)
		{
			AGridTileActor* GridTileActor = NewObject<AGridTileActor>();
			//AGridTileActor* GridTileActor = GetWorld()->SpawnActor<AGridTileActor>(AGridTileActor::StaticClass(), FVector(i * TileSize, j * TileSize, 0.0f), FRotator::ZeroRotator);
			GridTileActor->Rows = i;
			GridTileActor->Columns = j;
			GridTileActor->TileSize = TileSize;
			GridTileActor->TileColor = ETileColor::Transparent;
			GridTileArr[i].Add(GridTileActor);

			DrawSquare(FVector(i * TileSize, j * TileSize, 10.0f), TileSize, SquareVertices, SquareTriangles, SquareVertexColors);
		}
	}
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();

	TacticalStrikeGameState = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	if (TacticalStrikeGameState != nullptr)
		TacticalStrikeGameState->PlayerTurnStartDelegate.AddDynamic(this, &AGridActor::UpdateTurn);

	float LineStart;
	float LineEnd;

	for (int32 i = 0; i <= Rows; i++)
	{
		LineStart = TileSize * i;
		LineEnd = LineWidth();
		DrawLine(FVector(LineStart, 0.0f, 5.0f), FVector(LineStart, LineEnd, 5.0f), LineThiccness, LineVertices, LineTriangles);
	}

	for (int32 i = 0; i <= Columns; i++)
	{
		LineStart = TileSize * i;
		LineEnd = LineHeight();
		DrawLine(FVector(0.0f, LineStart, 5.0f), FVector(LineEnd, LineStart, 5.0f), LineThiccness, LineVertices, LineTriangles);
	}

	//DrawLine(FVector(0.0f, TileSize / 2, 10.0f), FVector(TileSize, TileSize / 2, 10.0f), TileSize, SquareVertices, SquareTriangles);

	//for (int32 i = 0; i <= Rows; i++)
	//{
	//	for (int32 j = 0; j <= Columns; j++)
	//	{
	//		DrawSquare(FVector(i * TileSize, j * TileSize, 10.0f), TileSize, SquareVertices, SquareTriangles, SquareVertexColors);
	//	}
	//}

	ProceduralMesh_Lines->CreateMeshSection(0, LineVertices, LineTriangles, {}, {}, {}, {}, true);
	ProceduralMesh_Squares->CreateMeshSection_LinearColor(0, SquareVertices, SquareTriangles, SquareNormals, SquareUV0, SquareVertexColors, {}, true);

	ProceduralMesh_Lines->SetMaterial(0, GridMaterialInstanceDynamic);
	ProceduralMesh_Squares->SetMaterial(0, SquareMaterial);

	//ProceduralMesh_Squares->SetBoundsScale(100.0f);
	//ProceduralMesh_Squares->UpdateLocalBounds();

	UpdateEnergyTile();
	DrawEnergyTile();


	//FVector2D Start = FVector2D(150, 250);
	//FVector2D End = FVector2D(850, 650);
	//float CellSize = 100.f;

	//TArray<FGridEdgeHit> Result = TraceGridEdges(Start, End, CellSize);

	//for (int32 i = 0; i < Result.Num(); i++)
	//{
	//	Result[i].Edge = ConvertEdge(Result[i].Edge);
	//}


	//for (const auto& Hit : Result)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Cell (%d, %d), Edge: %s"),
	//		Hit.Cell.X, Hit.Cell.Y, *Hit.Edge);
	//}

	//DebugDrawGridTrace(GetWorld(), Result, CellSize);

	//// 3) 전체 선도 그리기
	//DrawDebugLine(
	//	GetWorld(),
	//	FVector(Start, 0),
	//	FVector(End, 0),
	//	FColor::Green,
	//	false,
	//	60.f,
	//	0,
	//	4.f
	//);
}

void AGridActor::DrawLine(FVector StartVector, FVector EndVector, float Thiccness, TArray<FVector>& Vertices, TArray<int32>& Triangles)
{
	float HalfThiccness = Thiccness / 2;

	FVector Direction = FVector::CrossProduct((EndVector - StartVector).GetSafeNormal(0.00001f), FVector(0.0f, 0.0f, 1.0f));

	TArray<FVector> SetCorner;
	TArray<int32> SetTriangles;

	SetTriangles.Add(Vertices.Num() + 2);
	SetTriangles.Add(Vertices.Num() + 1);
	SetTriangles.Add(Vertices.Num() + 0);
	SetTriangles.Add(Vertices.Num() + 2);
	SetTriangles.Add(Vertices.Num() + 3);
	SetTriangles.Add(Vertices.Num() + 1);

	Triangles.Append(SetTriangles);

	SetCorner.Add(StartVector + (Direction * HalfThiccness));
	SetCorner.Add(EndVector + (Direction * HalfThiccness));
	SetCorner.Add(StartVector - (Direction * HalfThiccness));
	SetCorner.Add(EndVector - (Direction * HalfThiccness));

	Vertices.Append(SetCorner);
}

void AGridActor::DrawSquare(FVector StartVector, float Size, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FLinearColor>& VertexColors)
{
	FVector TopLeft = StartVector + FVector(0.0f, Size, 0.0f);
	FVector TopRight = StartVector + FVector(Size, Size, 0.0f);
	FVector BottomLeft = StartVector;
	FVector BottomRight = StartVector + FVector(Size, 0.0f, 0.0f);

	int32 StartIndex = Vertices.Num();

	TArray<FVector> SetVertices;
	TArray<int32> SetTriangles;
	TArray<FLinearColor> SetVertexColors;

	SetVertices.Add(BottomLeft);
	SetVertices.Add(BottomRight);
	SetVertices.Add(TopRight);
	SetVertices.Add(TopLeft);


	Vertices.Append(SetVertices);

	SetTriangles.Add(StartIndex + 0);
	SetTriangles.Add(StartIndex + 3);
	SetTriangles.Add(StartIndex + 2);

	SetTriangles.Add(StartIndex + 0);
	SetTriangles.Add(StartIndex + 2);
	SetTriangles.Add(StartIndex + 1);

	Triangles.Append(SetTriangles);

	SetVertexColors.Add(FLinearColor(0.0f, 0.0f, 0.0f, SquareOpacity_Transparent));
	SetVertexColors.Add(FLinearColor(0.0f, 0.0f, 0.0f, SquareOpacity_Transparent));
	SetVertexColors.Add(FLinearColor(0.0f, 0.0f, 0.0f, SquareOpacity_Transparent));
	SetVertexColors.Add(FLinearColor(0.0f, 0.0f, 0.0f, SquareOpacity_Transparent));

	VertexColors.Append(SetVertexColors);

	SquareNormals.Add(FVector(0.0f, 0.0f, 1.0f));
	SquareNormals.Add(FVector(0.0f, 0.0f, 1.0f));
	SquareNormals.Add(FVector(0.0f, 0.0f, 1.0f));
	SquareNormals.Add(FVector(0.0f, 0.0f, 1.0f));
}

float AGridActor::LineHeight()
{
	return Columns * TileSize;
}

float AGridActor::LineWidth()
{
	return Rows * TileSize;
}

void AGridActor::CreateMaterialInstance(FLinearColor Color, float Opacity)
{
	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(GridMaterialInstance, this);

	GridMaterialInstanceDynamic->SetVectorParameterValue(FName("Color"), Color);
	GridMaterialInstanceDynamic->SetScalarParameterValue(FName("Opacity"), Opacity);

	//return GridMaterialInstanceDynamic;
}

bool AGridActor::TileCheck(int32 Row, int32 Column)
{
	if (Row >= 0 && Row < Rows && Column >= 0 && Column < Columns)
		return true;
	else
		return false;
}

void AGridActor::SetGridRange(int32 TileRow, int32 TileColumn, int32 Range, EObjectOwner ObjectOwner)
{
	TQueue<TPair<int32, int32>> Queue;
	TSet<TPair<int32, int32>> Visited;

	Queue.Enqueue(TPair<int32, int32>(TileRow, TileColumn));
	Visited.Add(TPair<int32, int32>(TileRow, TileColumn));

	TArray<TPair<int32, int32>> Directions = {
		TPair<int32, int32>(1, 0),  
		TPair<int32, int32>(-1, 0), 
		TPair<int32, int32>(0, 1),
		TPair<int32, int32>(0, -1) 
	};

	while (!Queue.IsEmpty())
	{
		TPair<int32, int32> Current;
		Queue.Dequeue(Current);
		int32 Row = Current.Key;
		int32 Col = Current.Value;

		if (TileCheck(Row, Col))
		{
			AGridTileActor* Tile = GridTileArr[Row][Col];
			if (Tile)
			{
				GridTileArr[Row][Col]->IsEnergySupplying = true;
				if (ObjectOwner == EObjectOwner::Blue)
					GridTileArr[Row][Col]->TileOwner = ETileOwner::Blue;		
				else if (ObjectOwner == EObjectOwner::Red)
					GridTileArr[Row][Col]->TileOwner = ETileOwner::Red;
			}
		}

		for (const TPair<int32, int32>& Dir : Directions)
		{
			int32 NewRow = Row + Dir.Key;
			int32 NewCol = Col + Dir.Value;

			if (TileCheck(NewRow, NewCol))
			{
				if (!Visited.Contains(TPair<int32, int32>(NewRow, NewCol)))
				{
					int32 Distance = FMath::Abs(NewRow - TileRow) + FMath::Abs(NewCol - TileColumn);
					if (Distance <= Range)
					{
						Queue.Enqueue(TPair<int32, int32>(NewRow, NewCol));
						Visited.Add(TPair<int32, int32>(NewRow, NewCol));
					}
				}
			}
		}
	}
}


FIntPoint AGridActor::GetGridTile(FVector ObjectLocation)
{
	int32 TileRow = int32(FMath::Floor(ObjectLocation.X / 100));
	int32 TileColumn = int32(FMath::Floor(ObjectLocation.Y / 100));

	return FIntPoint(TileRow, TileColumn);
}

void AGridActor::SetDrawSquares(TArray<AGridTileActor*> SquareGridTileArr)
{
	for (const AGridTileActor* Grid : SquareGridTileArr)
	{
		//DrawSquare(FVector(Grid->Rows * TileSize, Grid->Columns * TileSize, 10.0f), TileSize, SquareVertices, SquareTriangles);
	}
}

void AGridActor::UpdateTileColor(int32 Row, int32 Column, ETileColor TileColor)
{
	int32 TileIndex = Row * Columns + Column;
	int32 VertexOffset = TileIndex * 4;
	switch (TileColor)
	{
	case ETileColor::Transparent:
		SquareVertexColors[VertexOffset] = FLinearColor(0.0f, 0.0f, 0.0f, SquareOpacity_Transparent);
		SquareVertexColors[VertexOffset + 1] = FLinearColor(0.0f, 0.0f, 0.0f, SquareOpacity_Transparent);
		SquareVertexColors[VertexOffset + 2] = FLinearColor(0.0f, 0.0f, 0.0f, SquareOpacity_Transparent);
		SquareVertexColors[VertexOffset + 3] = FLinearColor(0.0f, 0.0f, 0.0f, SquareOpacity_Transparent);
		break;
	case ETileColor::Red:
		SquareVertexColors[VertexOffset] = FLinearColor(1.0f, 0.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 1] = FLinearColor(1.0f, 0.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 2] = FLinearColor(1.0f, 0.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 3] = FLinearColor(1.0f, 0.0f, 0.0f, SquareOpacity);
		break;
	case ETileColor::Green:
		SquareVertexColors[VertexOffset] = FLinearColor(0.0f, 1.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 1] = FLinearColor(0.0f, 1.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 2] = FLinearColor(0.0f, 1.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 3] = FLinearColor(0.0f, 1.0f, 0.0f, SquareOpacity);
		break;
	case ETileColor::Yellow:
		SquareVertexColors[VertexOffset] = FLinearColor(1.0f, 1.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 1] = FLinearColor(1.0f, 1.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 2] = FLinearColor(1.0f, 1.0f, 0.0f, SquareOpacity);
		SquareVertexColors[VertexOffset + 3] = FLinearColor(1.0f, 1.0f, 0.0f, SquareOpacity);
		break;

	default:
		break;
	}
	GridTileArr[Row][Column]->TileColor = TileColor;
}

void AGridActor::UpdateEnergyTile()
{
	for (int32 i = 0; i < Rows; i++)
	{
		for (int32 j = 0; j < Columns; j++)
		{
			GridTileArr[i][j]->IsEnergySupplying = false;
		}
	}
	for (int32 i = 0; i < Rows; i++)
	{
		for (int32 j = 0; j < Columns; j++)
		{
			AGridTileActor* Tile = GridTileArr[i][j];
			//ADefaultBuilding* DefaultBuilding = Tile->OnBuildingObject;
			if (Tile != nullptr)
			{
				ADefaultBuilding* DefaultBuilding = Cast<ADefaultBuilding>(Tile->ObjectInfo.ObjectActor);
				if (DefaultBuilding != nullptr)
				{
					//UE_LOG(LogTemp, Log, TEXT("Owner: %d"), static_cast<int32>(DefaultBuilding->ObjectInfo.ObjectOwner));
					if (Tile->IsBuildingCenter && DefaultBuilding->ObjectInfo.ObjectState == EObjectState::Activated)
					{
						//UE_LOG(LogTemp, Log, TEXT("EnergyRange: %d"), DefaultBuilding->EnergyRange);
						if (DefaultBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Red)
							SetGridRange(i, j, DefaultBuilding->EnergyRange, EObjectOwner::Red);
						else if (DefaultBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Blue)
							SetGridRange(i, j, DefaultBuilding->EnergyRange, EObjectOwner::Blue);
					}
				}
			}
		}
	}
}

void AGridActor::DrawEnergyTile()
{
	//UE_LOG(LogTemp, Log, TEXT("vvvvvvvvvvssfwea"));
	for (int32 i = 0; i < Rows; i++)
	{
		for (int32 j = 0; j < Columns; j++)
		{
			if (CheckEnergySupply(i, j))
			{
				UpdateTileColor(i, j, ETileColor::Yellow);
			}
		}
	}
	ProceduralMesh_Squares->UpdateMeshSection_LinearColor(0, SquareVertices, SquareNormals, SquareUV0, SquareVertexColors, {}, false);
}

bool AGridActor::CheckGridObject(int32 TileRow, int32 TileColumn)
{

	//UE_LOG(LogTemp, Log, TEXT("%d"), GridTileArr[TileRow][TileColumn]->ObjectInfo.ObjectType);
	/*if (GridTileArr[TileRow][TileColumn]->ObjectInfo.ObjectActor != nullptr)
		UE_LOG(LogTemp, Log, TEXT("%s"), *GridTileArr[TileRow][TileColumn]->ObjectInfo.ObjectActor->GetName());*/

	if (GridTileArr[TileRow][TileColumn]->ObjectInfo.ObjectActor == nullptr)
		return true;
	else
		return false;
}

bool AGridActor::CheckEnergySupply(int32 TileRow, int32 TileColumn)
{
	if (GridTileArr[TileRow][TileColumn]->IsEnergySupplying)
		return true;
	else
		return false;
}

FIntPoint AGridActor::GetStartGridTile(int32 TileRow, int32 TileColumn, int32 GridSizeX, int32 GridSizeY, EObjectOwner ObjectOwner)
{
	int32 StartX = 0;
	int32 StartY = 0;

	if (ObjectOwner == EObjectOwner::Red)
	{
		StartX = TileRow - FMath::FloorToInt(float(GridSizeX) / 2.0f);
		StartY = TileColumn - FMath::FloorToInt(float(GridSizeY) / 2.0f);
	}
	else if (ObjectOwner == EObjectOwner::Blue)
	{
		StartX = TileRow - FMath::FloorToInt(float(GridSizeX) / 2.0f);
		StartY = TileColumn - FMath::FloorToInt(float(GridSizeY) / 2.0f);
	}

	return FIntPoint(StartX, StartY);
}

void AGridActor::DrawBuildingGrid(FIntPoint StartGridTile, int32 GridSizeX, int32 GridSizeY)
{
	ClearPreviousGrid();

	for (int32 i = 0; i < GridSizeX; i++)
	{
		for (int32 j = 0; j < GridSizeY; j++)
		{
			if (TileCheck(StartGridTile.X + i, StartGridTile.Y + j))
			{
				PreviousTileStruct.PreviousGrid = { StartGridTile.X + i, StartGridTile.Y + j };
				PreviousTileStruct.PreviousColor = GridTileArr[StartGridTile.X + i][StartGridTile.Y + j]->TileColor;
				PreviousBuildingGridArr.Add(PreviousTileStruct);

				//UE_LOG(LogTemp, Log, TEXT("X: %d, Y: %d"), StartGridTile.X + i, StartGridTile.Y + j);
				if (CheckBuildingGrid(StartGridTile.X + i, StartGridTile.Y + j))
					UpdateTileColor(StartGridTile.X + i, StartGridTile.Y + j, ETileColor::Green);
				else
					UpdateTileColor(StartGridTile.X + i, StartGridTile.Y + j, ETileColor::Red);
			}
		}
	}
	ProceduralMesh_Squares->UpdateMeshSection_LinearColor(0, SquareVertices, SquareNormals, SquareUV0, SquareVertexColors, {}, false);
}

bool AGridActor::CheckEnableBuilding(FIntPoint StartGridTile, int32 GridSizeX, int32 GridSizeY)
{
	for (int32 i = 0; i < GridSizeX; i++)
	{
		for (int32 j = 0; j < GridSizeY; j++)
		{
			if (!TileCheck(StartGridTile.X + i, StartGridTile.Y + j))
				return false;
			if (!CheckBuildingGrid(StartGridTile.X + i, StartGridTile.Y + j))
				return false;
		}
	}
	return true;
}

void AGridActor::ClearPreviousGrid()
{
	if (!PreviousBuildingGridArr.IsEmpty())
	{
		for (FPreviousTileStruct Point : PreviousBuildingGridArr)
		{
			UpdateTileColor(Point.PreviousGrid.X, Point.PreviousGrid.Y, Point.PreviousColor);
		}
		ProceduralMesh_Squares->UpdateMeshSection_LinearColor(0, SquareVertices, SquareNormals, SquareUV0, SquareVertexColors, {}, false);
		PreviousBuildingGridArr.Empty();
	}
}

bool AGridActor::CheckBuildingGrid(int32 Row, int32 Column)
{
	
	if (GridTileArr[Row][Column]->IsEnergySupplying == true && GridTileArr[Row][Column]->ObjectInfo.ObjectActor == nullptr)
		return true;
	else
		return false;
}

void AGridActor::SetTile_Building(FIntPoint BuildingGridPoint, ADefaultBuilding* DefaultBuilding, bool ObjectActivated)
{
	GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->ObjectInfo = DefaultBuilding->ObjectInfo;
	//GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->OnObjectCode = DefaultBuilding->BuildingType;
	//GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->OnBuildingObject = DefaultBuilding;
	//GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->IsObjectActivated = ObjectActivated;
	GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->IsBuildingCenter = true;

	AGridTileActor* GridTileActor = GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y];
	
	FIntPoint StartGridTile = GetStartGridTile(GridTileActor->Rows, GridTileActor->Columns,
		DefaultBuilding->GridSizeX, DefaultBuilding->GridSizeY, DefaultBuilding->ObjectInfo.ObjectOwner);

	for (int32 i = 0; i < DefaultBuilding->GridSizeX; i++)
	{
		for (int32 j = 0; j < DefaultBuilding->GridSizeY; j++)
		{
			if (TileCheck(StartGridTile.X + i, StartGridTile.Y + j))
			{
				GridTileArr[StartGridTile.X + i][StartGridTile.Y + j]->ObjectInfo = DefaultBuilding->ObjectInfo;
				if (ObjectActivated)
				{
					//SetTileDir(FIntPoint(StartGridTile.X + i, StartGridTile.Y + j));
					 
					
					//UE_LOG(LogTemp, Log, TEXT("%d, %d"), StartGridTile.X + i, StartGridTile.Y + j);
					//UE_LOG(LogTemp, Log, TEXT("[%d, %d], [%d, %d], [%d, %d], [%d, %d]"),
						//GridTileArr[StartGridTile.X + i - 1][StartGridTile.Y + j]->TileDirArr[0].TileDir,
						//GridTileArr[StartGridTile.X + i - 1][StartGridTile.Y + j]->TileDirArr[0].TileDirState,
						//GridTileArr[StartGridTile.X + i - 1][StartGridTile.Y + j]->TileDirArr[1].TileDir,
						//GridTileArr[StartGridTile.X + i - 1][StartGridTile.Y + j]->TileDirArr[1].TileDirState,
						//GridTileArr[StartGridTile.X + i - 1][StartGridTile.Y + j]->TileDirArr[2].TileDir,
						//GridTileArr[StartGridTile.X + i - 1][StartGridTile.Y + j]->TileDirArr[2].TileDirState,
						//GridTileArr[StartGridTile.X + i - 1][StartGridTile.Y + j]->TileDirArr[3].TileDir,
						//GridTileArr[StartGridTile.X + i - 1][StartGridTile.Y + j]->TileDirArr[3].TileDirState)
				}
				//UE_LOG(LogTemp, Log, TEXT("%d, %d"), StartGridTile.X + i, StartGridTile.Y + j);
				//GridTileArr[StartGridTile.X + i][StartGridTile.Y + j]->OnObjectCode = DefaultBuilding->BuildingType;
				//GridTileArr[StartGridTile.X + i][StartGridTile.Y + j]->OnBuildingObject = DefaultBuilding;
				//GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->IsObjectActivated = ObjectActivated;
			}
		}
	}
}

void AGridActor::SetTileDir(FIntPoint BuildingGridPoint)
{
	GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->TileDirArr[0].TileDirState = ETileDirState::Block;
	GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->TileDirArr[1].TileDirState = ETileDirState::Block;
	GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->TileDirArr[2].TileDirState = ETileDirState::Block;
	GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y]->TileDirArr[3].TileDirState = ETileDirState::Block;

	TArray<TPair<int32, int32>> Directions = {
	TPair<int8, int8>(1, 0),
	TPair<int8, int8>(-1, 0),
	TPair<int8, int8>(0, 1),
	TPair<int8, int8>(0, -1)
	};

	if (TileCheck(BuildingGridPoint.X + 1, BuildingGridPoint.Y))
	{
		if (GridTileArr[BuildingGridPoint.X + 1][BuildingGridPoint.Y]->TileDirArr[static_cast<int32>(ETileDir::Bottom)].TileDirState != ETileDirState::Block)
			GridTileArr[BuildingGridPoint.X + 1][BuildingGridPoint.Y]->TileDirArr[static_cast<int32>(ETileDir::Bottom)].TileDirState = ETileDirState::Hiding;
	}
	if (TileCheck(BuildingGridPoint.X - 1, BuildingGridPoint.Y))
	{
		if (GridTileArr[BuildingGridPoint.X - 1][BuildingGridPoint.Y]->TileDirArr[static_cast<int32>(ETileDir::Top)].TileDirState != ETileDirState::Block)
			GridTileArr[BuildingGridPoint.X - 1][BuildingGridPoint.Y]->TileDirArr[static_cast<int32>(ETileDir::Top)].TileDirState = ETileDirState::Hiding;
	}
	if (TileCheck(BuildingGridPoint.X, BuildingGridPoint.Y + 1))
	{
		if (GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y + 1]->TileDirArr[static_cast<int32>(ETileDir::Left)].TileDirState != ETileDirState::Block)
			GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y + 1]->TileDirArr[static_cast<int32>(ETileDir::Left)].TileDirState = ETileDirState::Hiding;
	}
	if (TileCheck(BuildingGridPoint.X, BuildingGridPoint.Y - 1))
	{
		if (GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y - 1]->TileDirArr[static_cast<int32>(ETileDir::Right)].TileDirState != ETileDirState::Block)
			GridTileArr[BuildingGridPoint.X][BuildingGridPoint.Y - 1]->TileDirArr[static_cast<int32>(ETileDir::Right)].TileDirState = ETileDirState::Hiding;
	}

}

void AGridActor::SetTile_Unit(FIntPoint UnitGridPoint, class ADefaultUnit* DefaultUnit)
{
	GridTileArr[UnitGridPoint.X][UnitGridPoint.Y]->ObjectInfo = DefaultUnit->ObjectInfo;
	//UE_LOG(LogTemp, Log, TEXT("UnitType: %s"), *GridTileArr[UnitGridPoint.X][UnitGridPoint.Y]->ObjectInfo.ObjectActor->GetName());
}

void AGridActor::RemoveTile_Unit(FIntPoint UnitGridPoint)
{
	GridTileArr[UnitGridPoint.X][UnitGridPoint.Y]->ClearObjectInfo();
}

void AGridActor::ViewGridTile()
{
	if (ProceduralMesh_Lines->IsVisible())
	{
		ProceduralMesh_Lines->SetVisibility(false);
		ProceduralMesh_Squares->SetVisibility(false);
	}
	else
	{
		ProceduralMesh_Lines->SetVisibility(true);
		ProceduralMesh_Squares->SetVisibility(true);
	}
}

void AGridActor::UpdateTurn()
{
	//UE_LOG(LogTemp, Log, TEXT("UPdate"));
	UpdateEnergyTile();
	DrawEnergyTile();
}

TArray<class AGridTileActor*> AGridActor::CheckAIEnegyTile()
{
	TArray<class AGridTileActor*> AIEnergyTileArr;

	for (int32 i = 0; i < Rows; i++)
	{
		for (int32 j = 0; j < Columns; j++)
		{
			if (GridTileArr[i][j]->TileOwner == ETileOwner::Red)
				AIEnergyTileArr.Add(GridTileArr[i][j]);
		}
	}
	return AIEnergyTileArr;
}

//bool AGridActor::CheckContiguousSubarray(TArray<FVector> Arr1, TArray<FVector> Arr2)
//{
//	if (Arr2.Num() < Arr1.Num())
//		return false;
//	for (int32 i = 0; i <= Arr2.Num() - Arr1.Num(); i++)
//	{
//		/*if (Arr1[0].Equals(Arr2[i], KINDA_SMALL_NUMBER))*/
//		//if (Arr1[0] == Arr2[i])
//		//{
//			bool bMatch = true;
//
//			for (int32 j = 0; j < Arr1.Num(); j++)
//			{
//				/*if (!Arr1[j].Equals(Arr2[i + j], KINDA_SMALL_NUMBER))*/
//				if (Arr1[j] != Arr2[i + j])
//				{
//					bMatch = false;
//					break;
//				}
//			}
//
//			if (bMatch)
//				return true;
//	//	}
//	}
//	return false;
//}



//void AGridActor::AddEdgePair(TArray<FGridEdgeHit>& Out, int X, int Y, const FString& Edge)
//{
//	Out.Add({ FIntPoint(X, Y), Edge });
//
//	if (Edge == "LEFT")
//		Out.Add({ FIntPoint(X - 1, Y), "RIGHT" });
//
//	else if (Edge == "RIGHT")
//		Out.Add({ FIntPoint(X + 1, Y), "LEFT" });
//
//	else if (Edge == "TOP")
//		Out.Add({ FIntPoint(X, Y + 1), "BOTTOM" });
//
//	else if (Edge == "BOTTOM")
//		Out.Add({ FIntPoint(X, Y - 1), "TOP" });
//}
//
//TArray<FGridEdgeHit> AGridActor::TraceGridEdges(const FVector2D& StartWorld, const FVector2D& EndWorld, float CellSize)
//{
//	TArray<FGridEdgeHit> Hits;
//
//	FVector2D A = StartWorld / CellSize;
//	FVector2D B = EndWorld / CellSize;
//
//	int X = FMath::FloorToInt(A.X);
//	int Y = FMath::FloorToInt(A.Y);
//
//	int EndX = FMath::FloorToInt(B.X);
//	int EndY = FMath::FloorToInt(B.Y);
//
//	float Dx = B.X - A.X;
//	float Dy = B.Y - A.Y;
//
//	int StepX = (Dx > 0) ? 1 : -1;
//	int StepY = (Dy > 0) ? 1 : -1;
//
//	float InvDx = (Dx != 0) ? 1.f / FMath::Abs(Dx) : TNumericLimits<float>::Max();
//	float InvDy = (Dy != 0) ? 1.f / FMath::Abs(Dy) : TNumericLimits<float>::Max();
//
//	float NextBoundaryX = (StepX > 0 ? (FMath::FloorToFloat(A.X) + 1 - A.X) : (A.X - FMath::FloorToFloat(A.X)));
//	float NextBoundaryY = (StepY > 0 ? (FMath::FloorToFloat(A.Y) + 1 - A.Y) : (A.Y - FMath::FloorToFloat(A.Y)));
//
//	float TMaxX = NextBoundaryX * InvDx;
//	float TMaxY = NextBoundaryY * InvDy;
//
//	float TDeltaX = InvDx;
//	float TDeltaY = InvDy;
//
//	while (X != EndX || Y != EndY)
//	{
//		if (TMaxX < TMaxY)
//		{
//			FString Edge = (StepX > 0) ? "RIGHT" : "LEFT";
//			AddEdgePair(Hits, X, Y, Edge);
//
//			X += StepX;
//			TMaxX += TDeltaX;
//		}
//		else if (TMaxX > TMaxY)
//		{
//			FString Edge = (StepY > 0) ? "TOP" : "BOTTOM";
//			AddEdgePair(Hits, X, Y, Edge);
//
//			Y += StepY;
//			TMaxY += TDeltaY;
//		}
//		else
//		{
//			FString Ev = (StepX > 0) ? "RIGHT" : "LEFT";
//			FString Eh = (StepY > 0) ? "TOP" : "BOTTOM";
//
//			AddEdgePair(Hits, X, Y, Ev);
//			AddEdgePair(Hits, X, Y, Eh);
//
//			X += StepX;
//			Y += StepY;
//
//			TMaxX += TDeltaX;
//			TMaxY += TDeltaY;
//		}
//	}
//
//	return Hits;
//}
//
//void AGridActor::DebugDrawGridTrace(UWorld* World, const TArray<FGridEdgeHit>& Hits, float CellSize)
//{
//	for (const auto& Hit : Hits)
//	{
//		DrawGridEdge(
//			World,
//			Hit.Cell,
//			Hit.Edge,
//			CellSize,
//			FColor::Red,
//			6.f,
//			3.f
//		);
//
//		float X = Hit.Cell.X * CellSize + CellSize * 0.5f;
//		float Y = Hit.Cell.Y * CellSize + CellSize * 0.5f;
//
//		FVector TextPos(X, Y, 50.f);
//
//		DrawEdgeText(
//			World,
//			TextPos,
//			FString::Printf(TEXT("(%d, %d) %s"), Hit.Cell.X, Hit.Cell.Y, *Hit.Edge),
//			60.0f
//		);
//	}
//}
//
//void AGridActor::DrawGridEdge(UWorld* World, const FIntPoint& Cell, const FString& Edge, float CellSize, FColor Color, float Thickness, float Duration)
//{
//	Thickness = 5.f;
//	Duration = 60.0f;
//	Color = FColor::Red;
//	FVector Start, End;
//
//	float X = Cell.X * CellSize;
//	float Y = Cell.Y * CellSize;
//
//	if (Edge == "BOTTOM")
//	{
//		Start = FVector(X, Y, 0);
//		End = FVector(X, Y + CellSize, 0);
//	}
//	else if (Edge == "TOP")
//	{
//		Start = FVector(X + CellSize, Y, 0);
//		End = FVector(X + CellSize, Y + CellSize, 0);
//	}
//	else if (Edge == "RIGHT")
//	{
//		Start = FVector(X, Y + CellSize, 0);
//		End = FVector(X + CellSize, Y + CellSize, 0);
//	}
//	else if (Edge == "LEFT")
//	{
//		Start = FVector(X, Y, 0);
//		End = FVector(X + CellSize, Y, 0);
//	}
//
//	DrawDebugLine(World, Start, End, Color, false, Duration, 0, Thickness);
//}
//
//void AGridActor::DrawEdgeText(UWorld* World, const FVector& Position, const FString& Text, float Duration = 60.0f)
//{
//	DrawDebugString(World, Position, Text, nullptr, FColor::White, Duration, false);
//}
//
//FString AGridActor::ConvertEdge(const FString& Edge)
//{
//	if (Edge == "RIGHT")  return "TOP";
//	if (Edge == "LEFT")   return "BOTTOM";
//	if (Edge == "TOP")    return "RIGHT";
//	if (Edge == "BOTTOM") return "LEFT";
//
//	return Edge;
//}