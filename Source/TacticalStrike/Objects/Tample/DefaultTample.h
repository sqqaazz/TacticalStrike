// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/UnitsArray.h"
#include "Characters/Units/RifleMan/RifleMan.h"
#include "Characters/Units/SwordMan/SwordMan.h"
#include "Characters/Units/Mutant/Mutant.h"
#include "DataTables/BuildingDataTables.h"
#include "GameMode/TacticalStrikeGameStateBase.h"
#include "Objects/CommanderMap.h"
#include "DefaultTample.generated.h"

/**
 * 
 */


UCLASS()
class TACTICALSTRIKE_API ADefaultTample : public ADefaultBuilding
{
	GENERATED_BODY()
public:
	ADefaultTample();

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	//FString RifleManStr;
	//FString SwordManStr;
	//FString MutantStr;
	//virtual void InitUnitClass(const FString& NewRifleManText, const FString& NewSwordManText, const FString& NewMutantText);

	//class ACommanderMap* SpawnCommanderMap;
	//FVector CheckUnitSpawnScale(UUnitsArray* UnitsInfo);
	//virtual void SpawnUnit(UUnitsArray* UnitsInfo, FVector UnitSpawnLocation);
	FString TampleColor;

	//유닛 카운트 장소에서 유닛 체크 후 필드에 스폰
	/*virtual void GetUnitArray();*/
	//FVector TampleUnitSpawnLocation;
	//TArray<AActor*> SpawnUnitArray;

	//UPROPERTY()
	//TSubclassOf<ARifleMan> SpawnRifleMan;
	//UPROPERTY()
	//TSubclassOf<ASwordMan> SpawnSwordMan;
	//UPROPERTY()
	//TSubclassOf<AMutant> SpawnMutant;

	//FBuildingTableRow* BuildingDataInfo;
};
