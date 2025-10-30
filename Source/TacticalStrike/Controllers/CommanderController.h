// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "DataTables/UnitDataTables.h"
#include "CommanderController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FResourceProductionDelegate, FString Team);

UCLASS()
class TACTICALSTRIKE_API ACommanderController : public APlayerController
{
	GENERATED_BODY()

public:
	ACommanderController();

	bool Building;
	void IsBuilding(ESpawnBuilding BuildingCode);
	void IsNotBuilding();

	bool EnterWidgetState;
	void IsEnterWidget();
	void IsNotEnterWidget();

	UPROPERTY()
	class UCommanderBaseWidget* BaseWidget;

	//대기열 추가
	void BuildingUnits(ESpawnBuilding BuildingType, ESpawnUnit UnitType);
	void BuildingUpgrade(uint8 UpgradeType);

	//대기열 마침
	void ResearchComplete(uint8 ResearchType, FString Team);

	UPROPERTY()
	float Mineral;
	UPROPERTY()
	float Gas;

	float ChangeMineral;
	float ChangeGas;

	void SetResource(uint32 MineralCost, uint32 GasCost, float DeltaTime);

	class UBuildingClickableComponent* BuildingClickableComponent;
	class USpawnBuildingComponent* SpawnBuildingComponent;

	//유닛 위젯 표기를 위해 사용.
	void SetUnitInfo(uint8 Type);
	void UpdateObjectInfo(FObjectInfo ObjectInfo);

	void SetDefaultObjectInfo();

	//스폰, 연구 델리게이트
	FResourceProductionDelegate ResourceProductionDelegate;

	//클릭한 액터 확인
	class AActor* ClickedDefaultObject = nullptr;

	//class ADefaultUnit* ClickedDefaultUnit = nullptr;
	//class ADefaultBuilding* ClickedDefaultBuilding = nullptr;

	//클릭 하이라이트 조정
	void SetObjectHighlight(AActor* ClickedActor, bool Visibility);
	//void DisableAllHighlight();

	UFUNCTION()
	void OnClickedEvent();

	void ViewGridTile();


	//class ADefaultSpawningActor* DefaultSpawningActor;
	//void SpawnUnit();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	UPROPERTY(VisibleAnywhere, Category = UI)
	TSubclassOf<class UCommanderBaseWidget> BaseWidgetClass;
	//class UCommanderBaseWidget* GetCommanderWidget() CommanderBaseWidget const;
	
private:

	FVector MouseLocation;
	FVector MouseDirection;

	//UPROPERTY()
	//TSubclassOf<ABuilding_Barracks> Spawn_Barracks;
	//라인 트레이스를 통해 액터를 건설할 위치를 구하는데 사용
	FHitResult Hit;
	FVector AdjustBuildingLocation;
	//float HitLocationX;
	//float HitLocationY;

	//ABuilding_Barracks* CheckSpawnBarracks;
	//ABuilding_Barracks* SpawnBarracks;
/*
	FVector AdjustLocation(FHitResult HitResult)*/;

	//클릭한 액터 정보를 가져올때 사용
	FHitResult MouseHitResult;
	class ADefaultBuilding* SelectedBuilding;

	class UTacticalStrikeGameInstance* GameInstance;
	FUnitTableRow* UnitDataArray;

	class ATacticalStrikeGameStateBase* GetWorldCommanderTimer;

	UFUNCTION()
	void UpdateWorldTimer();
	UFUNCTION()
	void UpdateTurn();

	class AGridActor* GridActor;
};
