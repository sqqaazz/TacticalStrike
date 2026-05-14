// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "GridTileActor.generated.h"

//UENUM(BlueprintType)
//enum class ETileOwner : uint8
//{
//	None UMETA(DisPlayName = "None"),
//	Red UMETA(DisPlayName = "Red"),
//	Blue UMETA(DisPlayName = "Blue")
//};
//
//UENUM(BlueprintType)
//enum class ETileColor : uint8
//{
//	Transparent UMETA(DisPlayName = "Transparent"),
//	Red UMETA(DisPlayName = "Red"),
//	Green UMETA(DisPlayName = "Blue"),
//	Yellow UMETA(DisPlayName = "Yellow")
//};
//
//UENUM(BlueprintType)
//enum class ETileDir : uint8
//{
//	Left UMETA(DisPlayName = "Left"),
//	Top UMETA(DisPlayName = "Top"),
//	Right UMETA(DisPlayName = "Right"),
//	Bottom UMETA(DisPlayName = "Bottom")
//};
//
//UENUM(BlueprintType)
//enum class ETileDirState : uint8
//{
//	None UMETA(DisPlayName = "None"),
//	Blank UMETA(DisPlayName = "Blank"),
//	Hiding UMETA(DisPlayName = "Hiding"),
//	Block UMETA(DisPlayName = "Block")
//};

//USTRUCT(BlueprintType)
//struct FTileDirStruct
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	ETileDir TileDir;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	ETileDirState TileDirState;
//};

UCLASS()
class TACTICALSTRIKE_API AGridTileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridTileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void PreInitializeComponents() override;
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	
	bool IsEnergySupplying;
	bool IsBuildingCenter;
	//bool IsObjectActivated;
	//int16 OnObjectCode;
	ETileOwner TileOwner;
	ETileColor TileColor;
	int32 Rows;
	int32 Columns;
	int32 TileSize;

	FObjectInfo ObjectInfo;

	TArray<FTileDirStruct> TileDirArr;

	//void DrawSquare(FVector StartVector, float Size, TArray<FVector>& Vertices, TArray<int32>& Triangles);
	//void DrawSquareTile();

	//UPROPERTY()
	//class UProceduralMeshComponent* ProceduralMesh_Squares;

	//UMaterialInstance* GridMaterialInstance;

	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic_Squares_Enable;
	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic_Squares_Disable;
	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic_Squares_Energy;

	//void CreateMaterialInstance(UMaterialInstanceDynamic* MaterialInstanceDynamic, FLinearColor Color, float Opacity);
private:
	//FLinearColor SquareColor_Enable;
	//UPROPERTY(EditAnyWhere, Category = Line)
	//FLinearColor SquareColor_Disable;
	//UPROPERTY(EditAnyWhere, Category = Line)
	//FLinearColor SquareColor_Energy;
	//UPROPERTY(EditAnyWhere, Category = Line)
	//float SquareOpacity;

	//TArray<FVector> SquareVertices;
	//TArray<int32> SquareTriangles;

	//UMaterialInstanceDynamic* GridMaterialInstanceDynamic;
};
