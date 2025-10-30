// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "DefaultSpawningActor.generated.h"

UCLASS()
class TACTICALSTRIKE_API ADefaultSpawningActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultSpawningActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* StaticMesh;

	void ResourceProductionComplete(FString Team);

	//액터 크기 구하기
	FVector GetBuildingScale(class ADefaultBuilding* BuildingInfo);

	UFUNCTION()
	void SpawnUnit(FObjectInfo ObjectInfo, ADefaultBuilding* SpawningBuilding);

private:
	//컨트롤러
	TArray<AActor*> CommanderUnitArray;
	class ACommanderController* CommanderController;
	class ACommanderAI* CommanderAI;

	//스폰 맵
	TArray<AActor*> SpawnUnitArray;
	class ACommanderMap* SpawnRedCommanderMap;
	class ACommanderMap* SpawnBlueCommanderMap;

	class ADefaultBuilding* DefaultBuilding;

	void SpawnCrystal(FVector SpawnLocation);

	UFUNCTION()
	FVector GetSpawnTileLocation(ADefaultBuilding* SpawningBuilding);


	UFUNCTION()
	void SpawnBuilding(ESpawnBuilding BuildingType, FVector SpawnLocation);

	//스폰할 유닛
	UPROPERTY()
	TSubclassOf<class ARifleMan> SpawnRifleMan_Blue;
	UPROPERTY()
	TSubclassOf<class ASwordMan> SpawnSwordMan_Blue;
	UPROPERTY()
	TSubclassOf<class AMutant> SpawnMutant_Blue;

	UPROPERTY()
	TSubclassOf<class ARifleMan> SpawnRifleMan_Red;
	UPROPERTY()
	TSubclassOf<class ASwordMan> SpawnSwordMan_Red;
	UPROPERTY()
	TSubclassOf<class AMutant> SpawnMutant_Red;

	//스폰할 건물
	UPROPERTY()
	TSubclassOf<class ABuilding_Barracks> Spawn_Barracks;
	UPROPERTY()
	TSubclassOf<class ABuilding_ResourceFacility> Spawn_ResourceFacility;
	UPROPERTY()
	TSubclassOf<class ABuilding_SynBioLab> Spawn_SynBioLab;
	UPROPERTY()
	TSubclassOf<class ABuilding_EnergyRepeater> Spawn_EnergyRepeater;
	UPROPERTY()
	TSubclassOf<class ABuilding_Crystal> Building_Crystal;


	class AGridActor* GridActor;

};
