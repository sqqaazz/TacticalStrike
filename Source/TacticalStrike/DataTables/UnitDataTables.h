// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "UnitDataTables.generated.h"

USTRUCT(BlueprintType)
struct FUnitTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuildTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Tech;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ArmorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProductionBuilding;
};


UCLASS()
class TACTICALSTRIKE_API AUnitDataTables : public AActor
{
	GENERATED_BODY()
};
