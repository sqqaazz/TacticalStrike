// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "BuildingDataTables.generated.h"

USTRUCT(BlueprintType)
struct FBuildingTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuildingCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuildTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Tech;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnergyRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridSizeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridSizeY;
};

UCLASS()
class TACTICALSTRIKE_API ABuildingDataTables : public AActor
{
	GENERATED_BODY()
};
