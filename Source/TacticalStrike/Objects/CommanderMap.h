// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Engine/Classes/Components/TextRenderComponent.h"
#include "DataTables/BuildingDataTables.h"
#include "CommanderMap.generated.h"

//DECLARE_MULTICAST_DELEGATE_TwoParams(FCountPlaceSpawnDelegate, uint8, FVector);
//DECLARE_MULTICAST_DELEGATE_TwoParams(FCountPlaceSpawnDelegate, uint8, FVector);

//카운트 장소에서 필드로 스폰시 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnitSpawnDelegate);
//건물에서 카운트 장소로 스폰시 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCountPlaceSpawnDelegate, uint8, UnitType, FVector, UnitLocation);

//건물 기반 위치 설정하고 스폰 명령을 내리는데 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpawnBuildingDelegate, uint8, BuildingType, FVector, SpawnDefaultLocation);


UCLASS()
class TACTICALSTRIKE_API ACommanderMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACommanderMap();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

private:
	//사용자 맵의 메쉬
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* CommanderMapMesh;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* CommanderMapPlaneMesh;

	class ATacticalStrikeGameStateBase* SpawnBlueUnit;

	UFUNCTION()
	void CheckUnitCount();

	UPROPERTY()
	TSubclassOf<class UUnitsArray> UnitsClass;

public:
	TArray<UUnitsArray*> UnitsArray;

	FUnitSpawnDelegate UnitSpawnDelegate;

	UPROPERTY(BlueprintAssignable)
	FCountPlaceSpawnDelegate CountPlaceSpawnDelegate;

	UPROPERTY(BlueprintAssignable)
	FSpawnBuildingDelegate SpawnBuildingDelegate;
	

	//건물에서 유닛 카운트 장소로 유닛 스폰 
	UFUNCTION()
	void BuildingUnitSpawn(FString Team, uint8 UnitType);
	//void SpawnUnit(uint8 UnitType, FVector UnitSpawnLocation);
	FVector CheckUnitSpawnScale(uint8 UnitType);
	//AI 건물 스폰
	UFUNCTION()
	void BuildingSpawn(uint8 BuildingType);

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* UnitCount_OneTime;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* UnitCount_FiveTimes;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* UnitCount_TwentyTimes;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* ResourcePlace;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* TechPlace;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BuildingPlace;



	//UTextRenderComponent* UnitCountRender_OneTime;
	//UTextRenderComponent* UnitCountRender_FiveTimes;
	//UTextRenderComponent* UnitCountRender_TwentyTimes;

private:
	uint8 ConvertUnitType(FOverlapResult TargetActor);

	void AddUnitCount(TArray<FOverlapResult> TargetResultArray, uint8 AddCount);

	FVector UnitCount_OneTime_Location;
	FVector UnitCount_FiveTimes_Location;
	FVector UnitCount_TwentyTimes_Location;

	// 컨트롤러
	TArray<AActor*> CommanderUnitArray;
	class ACommanderAI* CommanderAI;

	class UTacticalStrikeGameInstance* GameInstance;
	FBuildingTableRow* BuildingDataTable;

	FVector BlueTeamSpawnVector;
	FVector RedTeamSpawnVector;
};
