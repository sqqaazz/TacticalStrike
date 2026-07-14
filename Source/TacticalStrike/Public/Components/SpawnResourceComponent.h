// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALSTRIKE_API USpawnResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpawnResourceComponent();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	class AGridActor* GridActor;
	UPROPERTY()
	class ADefaultSpawningActor* DefaultSpawningActor;

	UPROPERTY()
	int32 Rows;
	UPROPERTY()
	int32 Columns;

	UPROPERTY()
	int32 Radius;

	UPROPERTY()
	TSet<FIntPoint> Occupied;
	UPROPERTY()
	TSet<FIntPoint> Blocked;

	UPROPERTY()
	int32 SpawnResourceCount;

	void ArrangementResourceField();
	void SpawnResource();

	void MakeResourceCluster(int32 ClusterSize);

	void MakeBlockedTile();
	void MakeBlockedTile_BuildingTile();

	FIntPoint GetClusterCenter();

	bool TileCheck(FIntPoint CheckTile);


};
