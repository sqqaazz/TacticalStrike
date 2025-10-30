// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTables/BuildingDataTables.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Objects/GridActor.h"
#include "DefaultBuilding.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildingHPChanged, ADefaultBuilding*);
DECLARE_MULTICAST_DELEGATE(FOnBuildingHPChanged);
enum class EBuildingOwner : uint8
{
	None UMETA(DisPlayName = "None"),
	Red UMETA(DisPlayName = "Red"),
	Blue UMETA(DisPlayName = "Blue")
};

UCLASS()
class TACTICALSTRIKE_API ADefaultBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultBuilding();

	uint8 BuildingType;

	int32 DefaultHP;
	int32 CurrentHP;
	int32 Armor;
	int32 GridSizeX;
	int32 GridSizeY;
	int32 EnergyRange;
	int32 BuildTime;
	int32 CurrentBuildTime;

	FObjectInfo ObjectInfo;


	class UBuildingClickableComponent* ClickableComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	class UTacticalStrikeGameInstance* GameInstance;

	//건물의 메쉬와 머티리얼, 자식 클래스에서 초기화
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DefaultBuildingMesh;

	UMaterialInterface* DefaultBuildingMat;

	UMaterialInterface* BuildEnableMat;
	UMaterialInterface* BuildDisableMat;

	virtual void SetBuildingScale();

	void BuildBuilding();

	class AGridActor* GridActor;
public:	
	FOnBuildingHPChanged OnBuildingHPChanged;

	virtual void SetEnableMat();
	virtual void SetDisableMat();
	virtual void SetBasicMat();

	void SetBuildingCustomDepth(bool Result);

	FBuildingTableRow* BuildingDataInfo;

	EObjectOwner ObjectOwner;
	EObjectState ObjectState;

	void Set_NiagaraComponent_ObjectSelected_Scale();

	void Set_NiagaraComponent_ObjectSelected_Visibility(bool Visibility);

	void ActivateBuilding();
private:
	USceneComponent* RootScene;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* NiagaraComponent_ObjectSelected;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* NiagaraSystem_ObjectSelected;

	class ATacticalStrikeGameStateBase* TacticalStrikeGameStateBase;

	UFUNCTION()
	void UpdateTurn();
};
