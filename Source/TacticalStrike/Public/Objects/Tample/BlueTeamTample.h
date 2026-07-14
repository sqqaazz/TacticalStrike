// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "TacticalStrikeInterface.h"
//#include "UnitsArray.h"
//#include "RifleMan.h"
//#include "SwordMan.h"
//#include "Mutant.h"
#include "DefaultTample.h"
#include "BlueTeamTample.generated.h"

UCLASS()
class TACTICALSTRIKE_API ABlueTeamTample : public ADefaultTample
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlueTeamTample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UFUNCTION()
	//void GetUnitArray() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
private:

	//UPROPERTY()
	//int32 Health;

	//UPROPERTY()
	//int32 Armor;

	//UPROPERTY()
	//UStaticMeshComponent* Mesh;

	////class ATacticalStrikeGameStateBase* SpawnBlueUnit;

	//class ACommanderMap* SpawnCommanderMap;

	//void SpawnUnit(UUnitsArray* UnitsInfo, FVector UnitSpawnLocation) override;

	//TArray<AActor*> SpawnUnitArray;

	//FVector CheckUnitSpawnScale(UUnitsArray* UnitsInfo);

	//UPROPERTY()
	//TSubclassOf<ARifleMan> SpawnRifleMan;
	//UPROPERTY()
	//TSubclassOf<ASwordMan> SpawnSwordMan;
	//UPROPERTY()
	//TSubclassOf<AMutant> SpawnMutant;

};
