// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/DefaultSpawningActor.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "SpawnBuildingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALSTRIKE_API USpawnBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnBuildingComponent();

	class ACommanderController* CommanderController;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void IsBuilding(ESpawnBuilding BuildingCode);
	void IsNotBuilding();

	void IsEnterWidget();
	void IsNotEnterWidget();

	/*UFUNCTION()
	void SpawnBuildings();*/

	UFUNCTION()
	void SpawnBuildings_Grid();

	UFUNCTION()
	void CheckEnableBuilding();

	bool IsEnableBuilding;

private:
	void CheckTraceResult(FVector MouseLocation, FVector MouseDirection);
	void CheckTraceResult_Grid(FVector MouseLocation, FVector MouseDirection);

	class UTacticalStrikeGameInstance* GameInstance;
	//건물이 위치할 장소 표기할때 사용
	FVector SpawnLocation;
	FVector SpawnDirection;
	FHitResult Hit;
	FVector AdjustBuildingLocation;
	FVector AdjustLocation(FHitResult HitResult);

	//FHitResult MouseHitResult;

	UPROPERTY()
	TSubclassOf<class ADefaultBuilding> Spawn_DefaultBuilding;

	class ADefaultBuilding* DefaultBuilding;
	//건물 정보 임시 저장
	class ADefaultBuilding* DefaultBuilding_Temp;

	void SpawnBuildingCode(ESpawnBuilding BuildingCode, EObjectOwner ObjectOwner, FVector BuildingLocation);
	ESpawnBuilding CurrentBuildingCode;
	FVector DefaultBuildingLocation;
	//ADefaultBuilding* SpawnBuildingInfo();

	//건물들의 클래스
	UPROPERTY()
	TSubclassOf<class ABuilding_Barracks> Building_Barracks;
	UPROPERTY()
	TSubclassOf<class ABuilding_SynBioLab> Building_SynBioLab;
	UPROPERTY()
	TSubclassOf<class ABuilding_ResourceFacility> Building_ResourceFacility;
	UPROPERTY()
	TSubclassOf<class ABuilding_EnergyRepeater> Building_EnergyRepeater;
	//Tick상태 제어
	bool TickIsActived;


	class AGridActor* GridActor;

	struct FBuildingTableRow* BuildingDataInfo;

	int32 CurTileRow = -1;
	int32 CurTileColumn = -1;

	int32 BuildingGridSizeX;
	int32 BuildingGridSizeY;
};
