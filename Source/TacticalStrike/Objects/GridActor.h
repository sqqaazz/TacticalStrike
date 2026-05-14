// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/GridTileActor.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "GridActor.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FPreviousTileStruct
{
	GENERATED_USTRUCT_BODY()
public:
	FIntPoint PreviousGrid;
	ETileColor PreviousColor;
};


UCLASS()
class TACTICALSTRIKE_API AGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
public:	
	// Called every frame
	///virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UProceduralMeshComponent* ProceduralMesh_Squares;
	UPROPERTY()
	class UProceduralMeshComponent* ProceduralMesh_Lines;
	UPROPERTY()
	class UStaticMeshComponent* GridCollisionMesh;

	UPROPERTY(EditAnyWhere, Category = Line)
	float TileSize;

	FIntPoint GetGridTile(FVector ObjectLocation);

	bool TileCheck(int32 Row, int32 Column);

	bool CheckGridObject(int32 TileRow, int32 TileColumn);
	bool CheckEnergySupply(int32 TileRow, int32 TileColumn);

	FIntPoint GetStartGridTile(int32 TileRow, int32 TileColumn, int32 GridSizeX, int32 GridSizeY, EObjectOwner ObjectOwner);

	void DrawBuildingGrid(FIntPoint StartGridTile, int32 GridSizeX, int32 GridSizeY);
	bool CheckEnableBuilding(FIntPoint StartGridTile, int32 GridSizeX, int32 GridSizeY);

	FPreviousTileStruct PreviousTileStruct;
	TArray<FPreviousTileStruct> PreviousBuildingGridArr;
	void ClearPreviousGrid();
	bool CheckBuildingGrid(int32 Row, int32 Column);


	void SetTile_Building(FIntPoint BuildingGridPoint, class ADefaultBuilding* DefaultBuilding, bool ObjectActivated);
	void SetTile_Unit(FIntPoint UnitGridPoint, class ADefaultUnit* DefaultUnit);

	void SetTileDir(FIntPoint BuildingGridPoint);

	void ViewGridTile();

	UFUNCTION()
	void UpdateTurn();

	void SetUnitSpawnGrid(FIntPoint StartGrid);

	TArray<TArray<class AGridTileActor*>> GridTileArr;

	TArray<class AGridTileActor*> CheckAIEnegyTile();

	/*void AddEdgePair(TArray<FGridEdgeHit>& Out, int X, int Y, const FString& Edge);

	TArray<FGridEdgeHit> TraceGridEdges(
		const FVector2D& StartWorld,
		const FVector2D& EndWorld,
		float CellSize
	);

	void DebugDrawGridTrace(
		UWorld* World,
		const TArray<FGridEdgeHit>& Hits,
		float CellSize
	);

	void DrawGridEdge(
		UWorld* World,
		const FIntPoint& Cell,
		const FString& Edge,
		float CellSize,
		FColor Color,
		float Thickness,
		float Duration
	);

	void DrawEdgeText(
		UWorld* World,
		const FVector& Position,
		const FString& Text,
		float Duration
	);


	FString ConvertEdge(const FString& Edge);*/

private:

	void DrawLine(FVector StartVector, FVector EndVector, float Thiccness, TArray<FVector>& Vertices, TArray<int32>& Triangles);
	
	//SectionIndex 0 = 
	///SectionIndex 1 = Energy
	void DrawSquare(FVector StartVector, float Size, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FLinearColor>& VerterColors);

	void UpdateTileColor(int32 Row, int32 Column, ETileColor TileColor);
	float LineHeight();
	float LineWidth();

	UPROPERTY(EditAnyWhere, Category = Line)
	int32 Rows;
	UPROPERTY(EditAnyWhere, Category = Line)
	int32 Columns;
	UPROPERTY(EditAnyWhere, Category = Line)
	float LineThiccness;
	UPROPERTY(EditAnyWhere, Category = Line)
	FLinearColor LineColor;
	UPROPERTY(EditAnyWhere, Category = Line)
	FLinearColor SquareColor_Enable;
	UPROPERTY(EditAnyWhere, Category = Line)
	FLinearColor SquareColor_Disable;
	UPROPERTY(EditAnyWhere, Category = Line)
	FLinearColor SquareColor_Energy;
	UPROPERTY(EditAnyWhere, Category = Line)
	float LineOpacity;
	UPROPERTY(EditAnyWhere, Category = Line)
	float SquareOpacity;
	UPROPERTY(EditAnyWhere, Category = Line)
	float SquareOpacity_Transparent;

	UMaterialInstance* GridMaterialInstance;

	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic_Lines;
	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic_Squares_Enable;
	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic_Squares_Disable;
	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic_Squares_Energy;

	void CreateMaterialInstance(FLinearColor Color, float Opacity);
	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* GridMaterialInstanceDynamic;

	UPROPERTY(VisibleAnywhere)
	UMaterial* SquareMaterial;

	TArray<FVector> LineVertices;
	TArray<int32> LineTriangles;
	TArray<FVector> SquareVertices;
	TArray<int32> SquareTriangles;
	TArray<FLinearColor> SquareVertexColors;
	TArray<FVector> SquareNormals;
	TArray<FVector2D> SquareUV0;
	//TArray<FProcMeshTangent> SquareTangents;

	TSet<class AGridTileActor*> EnergyTileArr;

	void SetGridRange(int32 TileRow, int32 TileColumn, int32 Range, EObjectOwner ObjectOwner);

	void SetDrawSquares(TArray<AGridTileActor*> SquareGridTileArr);

	void UpdateEnergyTile();
	void DrawEnergyTile();

	//bool CheckContiguousSubarray(TArray<FVector> Arr1, TArray<FVector> Arr2);

	class ATacticalStrikeGameStateBase* TacticalStrikeGameState;
};
