// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GridTileActor.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AGridTileActor::AGridTileActor()
{
	//ProceduralMesh_Squares = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GridProceduralMesh_TileSquares"));
	PrimaryActorTick.bCanEverTick = false;

	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> MATERIALINSTANCE(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Grid.MI_Grid'"));
	//if (MATERIALINSTANCE.Succeeded())
	//	GridMaterialInstance = MATERIALINSTANCE.Object;

	IsEnergySupplying = false;
	IsBuildingCenter = false;
	//IsObjectActivated = false;
	//OnBuildingObject = nullptr;
	//OnUnitObject = nullptr;
	TileOwner = ETileOwner::None;
	TileColor = ETileColor::Transparent;
	//OnObjectCode = -1;
	Rows = -1;
	Columns = -1;

	TileDirArr.Add(FTileDirStruct{ ETileDir::Left, ETileDirState::Blank });
	TileDirArr.Add(FTileDirStruct{ ETileDir::Top, ETileDirState::Blank });
	TileDirArr.Add(FTileDirStruct{ ETileDir::Right, ETileDirState::Blank });
	TileDirArr.Add(FTileDirStruct{ ETileDir::Bottom, ETileDirState::Blank });


	//SquareOpacity = 0.7f;

	//SquareColor_Enable = FLinearColor::Green;
	//SquareColor_Disable = FLinearColor::Red;
	//SquareColor_Energy = FLinearColor::Green;

	//RootComponent = ProceduralMesh_Squares;
}

// Called when the game starts or when spawned
void AGridTileActor::BeginPlay()
{
	Super::BeginPlay();

	//GridMaterialInstanceDynamic_Squares_Enable = CreateMaterialInstance(SquareColor_Enable, SquareOpacity);
	//GridMaterialInstanceDynamic_Squares_Disable = CreateMaterialInstance(SquareColor_Disable, SquareOpacity);
	//GridMaterialInstanceDynamic_Squares_Energy = CreateMaterialInstance(SquareColor_Energy, SquareOpacity);
	//DrawSquareTile();
}

void AGridTileActor::ClearObjectInfo()
{
	ObjectInfo.ObjectActor = nullptr;
	ObjectInfo.CurrentBuildTime = 0;
	ObjectInfo.CurrentHP = 0;
	ObjectInfo.ObjectState = EObjectState::None;
	ObjectInfo.ObjectType = 0;
}

//void AGridTileActor::PreInitializeComponents()
//{
//	Super::PreInitializeComponents();
//
//	GridMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(GridMaterialInstance, this);
//	CreateMaterialInstance(GridMaterialInstanceDynamic, SquareColor_Enable, SquareOpacity);
//}

//void AGridTileActor::DrawSquare(FVector StartVector, float Size, TArray<FVector>& Vertices, TArray<int32>& Triangles)
//{
//	FVector TopLeft = StartVector + FVector(0.0f, Size, 0.0f);
//	FVector TopRight = StartVector + FVector(Size, Size, 0.0f);
//	FVector BottomLeft = StartVector;
//	FVector BottomRight = StartVector + FVector(Size, 0.0f, 0.0f);
//
//	int32 StartIndex = Vertices.Num();
//
//	TArray<FVector> SetVertices;
//	TArray<int32> SetTriangles;
//
//	SetVertices.Add(BottomLeft);
//	SetVertices.Add(BottomRight);
//	SetVertices.Add(TopRight);
//	SetVertices.Add(TopLeft);
//
//	Vertices.Append(SetVertices);
//
//	SetTriangles.Add(StartIndex + 0);
//	SetTriangles.Add(StartIndex + 3);
//	SetTriangles.Add(StartIndex + 2);
//
//	SetTriangles.Add(StartIndex + 0);
//	SetTriangles.Add(StartIndex + 2);
//	SetTriangles.Add(StartIndex + 1);
//
//	Triangles.Append(SetTriangles);
//
//}

//void AGridTileActor::DrawSquareTile()
//{
//	if (Rows == -1 || Columns == -1)
//		return;
//
//	FVector SquareVector = FVector(Rows + 10.0f, Columns + 10.0f, 10.0f);
//	DrawSquare(SquareVector, TileSize, SquareVertices, SquareTriangles);
//	//UE_LOG(LogTemp, Log, TEXT("X: %f, Y: %f"), SquareVertices[0].X, SquareVertices[0].Y);
//	ProceduralMesh_Squares->SetMaterial(0, GridMaterialInstanceDynamic);
//	ProceduralMesh_Squares->SetBoundsScale(100.0f);
//	ProceduralMesh_Squares->CreateMeshSection(0, SquareVertices, SquareTriangles, {}, {}, {}, {}, false);
//
//
//}


//void AGridTileActor::CreateMaterialInstance(UMaterialInstanceDynamic* MaterialInstanceDynamic, FLinearColor Color, float Opacity)
//{
//
//	GridMaterialInstanceDynamic->SetVectorParameterValue(FName("Color"), Color);
//	GridMaterialInstanceDynamic->SetScalarParameterValue(FName("Opacity"), Opacity);
//
//	//return GridMaterialInstanceDynamic;
//}

