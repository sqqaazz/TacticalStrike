// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "UpgradeDataTables.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UpgradeCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuildTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Tech;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProductionBuilding;
};


UCLASS()
class TACTICALSTRIKE_API AUpgradeDataTables : public AActor
{
	GENERATED_BODY()
};
