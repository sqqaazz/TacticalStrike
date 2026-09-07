// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTables/BuildingDataTables.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Objects/GridActor.h"
#include "DefaultBuilding.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildingHPChanged, ADefaultBuilding*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildingHPChanged, ADefaultBuilding*);
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
	UPROPERTY()
	uint8 BuildingType;
	UPROPERTY()
	int32 DefaultHP;
	UPROPERTY()
	int32 CurrentHP;
	UPROPERTY()
	int32 Armor;
	UPROPERTY()
	int32 GridSizeX;
	UPROPERTY()
	int32 GridSizeY;
	UPROPERTY()
	int32 EnergyRange;
	UPROPERTY()
	int32 BuildTime;
	UPROPERTY()
	int32 CurrentBuildTime;

	FObjectInfo ObjectInfo;

	UPROPERTY()
	class UBuildingClickableComponent* ClickableComponent;
	UPROPERTY()
	AController* OwnerController;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	class UTacticalStrikeGameInstance* GameInstance;

	//건물의 메쉬와 머티리얼, 자식 클래스에서 초기화
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DefaultBuildingMesh;

	
	UPROPERTY(VisibleAnywhere)
	UGeometryCollectionComponent* DefaultBuildingFracture;

	UMaterialInterface* DefaultBuildingMat;

	UMaterialInterface* BuildEnableMat;
	UMaterialInterface* BuildDisableMat;

	virtual void SetBuildingScale();

	void BuildBuilding();

	UPROPERTY(VisibleAnywhere)
	class AGridActor* GridActor;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;
public:	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;


	FOnBuildingHPChanged OnBuildingHPChanged;

	float GetHealthRatio();

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

	void SetBuildingCollision();

	void ExplodeBuilding();
	void DestroyBuilding();
private:
	//USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* NiagaraComponent_ObjectSelected;
	UPROPERTY(VisibleAnywhere)
	class UNiagaraSystem* NiagaraSystem_ObjectSelected;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* NiagaraComponent_Explosion;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystem* ParticleSysystem_Fire;
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleComponent_Fire;

	FTimerHandle DestroyTimerHandle;

	class ATacticalStrikeGameStateBase* TacticalStrikeGameStateBase;

	UFUNCTION()
	void UpdateTurn();
};
