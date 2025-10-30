// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "UpgradeDataTables.h"
#include "BuildingClickableComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALSTRIKE_API UBuildingClickableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingClickableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//class UTacticalStrikeGameInstance* GameInstance;
	//진행상황 저장
	TArray<struct FObjectInfo> UnitDataArray;
	void GetResearchTime(uint8 ResearchTime);
	uint8 DefaultResearchTime;

	uint8 ResearchType;

	float BuildPercent;
	float ResearchPercent;


	UFUNCTION()
	void UpdateBuildingHP(/*ADefaultBuilding* ClickedDefaultBuilding*/);
	UFUNCTION()
	void UpdateBuildingState();
private:
	class UTacticalStrikeGameInstance* GameInstance;
	UStaticMeshComponent* MeshComponent;
	
	UFUNCTION()
	void ClickEvent(AActor* TouchedActor, FKey ButtonPressed);

	float CurBuildTime;
	float CurResearchTime;

	TArray<AActor*> SpawnUnitArray;
	class ACommanderMap* SpawnRedCommanderMap;
	class ACommanderMap* SpawnBlueCommanderMap;

	class ADefaultBuilding* DefaultBuilding;
	class ACommanderController* CommanderController;

	void SetUnitBuildingState(float DeltaTime);
	void SetResearchingState(float DeltaTime);

	struct FUpgradeTableRow* UpgradeDataInfo;

	class ADefaultSpawningActor* DefaultSpawningActor;
};
