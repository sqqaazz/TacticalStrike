// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include "Building_Barracks.h"
#include "TacticalStrikeGameInstance.generated.h"

struct FUnitTableRow;
struct FBuildingTableRow;
struct FUpgradeTableRow;
class UDataTable;

UENUM(BlueprintType)
enum class ESpawnUnit : uint8
{
	None = 0 UMETA(DisPlayName = "None"),
	RifleMan = 1 UMETA(DisPlayName = "RifleMan"),
	SwordMan = 2 UMETA(DisPlayName = "SwordMan"),
	Mutant = 3 UMETA(DisPlayName = "Mutant")
};

UENUM(BlueprintType)
enum class ESpawnBuilding : uint8
{
	None = 0 UMETA(DisPlayName = "None"),
	Barracks = 101 UMETA(DisPlayName = "Barracks"),
	SynBioLab = 102 UMETA(DisPlayName = "SynBioLab"),
	EnergyRepeater = 121 UMETA(DisPlayName = "EnergyRepeater"),
	ResourceFacility = 202 UMETA(DisPlayName = "ResourceFacility")
};

UENUM(BlueprintType)
enum class ESpawnObject : uint8
{
	None = 0 UMETA(DisPlayName = "None"),
	RifleMan = 1 UMETA(DisPlayName = "RifleMan"),
	SwordMan = 2 UMETA(DisPlayName = "SwordMan"),
	Mutant = 3 UMETA(DisPlayName = "Mutant"),
	Barracks = 101 UMETA(DisPlayName = "Barracks"),
	SynBioLab = 102 UMETA(DisPlayName = "SynBioLab"),
	EnergyRepeater = 121 UMETA(DisPlayName = "EnergyRepeater"),
	Tample = 201 UMETA(DisPlayName = "Tample"),
	ResourceFacility = 202 UMETA(DisPlayName = "ResourceFacility")
};

UENUM(BlueprintType)
enum class EObjectState : uint8
{
	None = 0 UMETA(DisPlayName = "None"),
	DeActivated UMETA(DisPlayName = "DeActivated"),
	Activated UMETA(DisPlayName = "Activated"),
	BuildWaited UMETA(DisPlayName = "BuildWaited"),
	Researched UMETA(DisPlayName = "Researched")
};

UENUM(BlueprintType)
enum class EObjectOwner : uint8
{
	None = 0 UMETA(DisPlayName = "None"),
	Red UMETA(DisPlayName = "Red"),
	Blue UMETA(DisPlayName = "Blue")
};

UENUM(BlueprintType)
enum class ETileOwner : uint8
{
	None UMETA(DisPlayName = "None"),
	Red UMETA(DisPlayName = "Red"),
	Blue UMETA(DisPlayName = "Blue")
};

UENUM(BlueprintType)
enum class ETileColor : uint8
{
	Transparent UMETA(DisPlayName = "Transparent"),
	Red UMETA(DisPlayName = "Red"),
	Green UMETA(DisPlayName = "Blue"),
	Yellow UMETA(DisPlayName = "Yellow")
};

UENUM(BlueprintType)
enum class ETileDir : uint8
{
	None UMETA(DisPlayName = "None"),
	Left UMETA(DisPlayName = "Left"),
	Top UMETA(DisPlayName = "Top"),
	Right UMETA(DisPlayName = "Right"),
	Bottom UMETA(DisPlayName = "Bottom")
};

UENUM(BlueprintType)
enum class ETileDirState : uint8
{
	None UMETA(DisPlayName = "None"),
	Blank UMETA(DisPlayName = "Blank"),
	Hiding UMETA(DisPlayName = "Hiding"),
	Block UMETA(DisPlayName = "Block")
};

USTRUCT(BlueprintType)
struct FTileDirStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileDir TileDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileDirState TileDirState;
};

USTRUCT(BlueprintType)
struct FGridEdgeHit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Cell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileDir Edge;
};

USTRUCT(BlueprintType)
struct FObjectInfo
{
    GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ObjectType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentHP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObjectState ObjectState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuildTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentBuildTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObjectOwner ObjectOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ObjectActor;

    FObjectInfo()
        : ObjectType(0), CurrentHP(0), ObjectState(EObjectState::None), BuildTime(0), CurrentBuildTime(0), ObjectOwner(EObjectOwner::None), Actions(0), ObjectActor(nullptr)
    {}

	FObjectInfo(uint8 InObjectType, int32 InCurrentHP, EObjectState InObjectState, int32 InBuildTime, int32 InCurrentBuildTime, EObjectOwner InObjectOwner, uint8 InActions, AActor* InObjectActor)
		: ObjectType(InObjectType), CurrentHP(InCurrentHP), ObjectState(InObjectState), BuildTime(InBuildTime), CurrentBuildTime(InCurrentBuildTime), ObjectOwner(InObjectOwner), Actions(InActions), ObjectActor(InObjectActor)
	{}
};


UCLASS()
class TACTICALSTRIKE_API UTacticalStrikeGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UTacticalStrikeGameInstance();
public:
	//오브젝트 데이터 데이블 불러오기
	TArray<FUnitTableRow*> GetAllUnitTable();
	FUnitTableRow* GetUnitTable(int32 UnitType);
	FBuildingTableRow* GetBuildingTable(int32 BuildingType);
	FUpgradeTableRow* GetUpgradeTable(int32 UpgradeType);

	//투명 이미지
	UMaterial* Texture_Transparency;

	//건설 이미지
	UTexture2D* Texture_BuildIcon;
	UTexture2D* Texture_TechIcon;
	UTexture2D* Texture_Empty;
	UTexture2D* Texture_StopBuilding;

	//유닛, 건물 이미지
	UMaterial* Texture_RifleMan;
	UMaterial* Texture_SwordMan;
	UMaterial* Texture_Mutant;

	UMaterial* Texture_Barracks;
	UMaterial* Texture_SynBioLab;
	UMaterial* Texture_ResourceFacility;
	UMaterial* Texture_Tample;
	UMaterial* Texture_EnergyRepeater;
	//업그레이드 이미지
	UTexture2D* Texture_ResourceUpgrade;

	//UI 이미지
	UTexture2D* Texture_SelectedButtonImage_Normal;
	UTexture2D* Texture_SelectedButtonImage_HOvered;
	UTexture2D* Texture_SelectedButtonImage_Pressed;
	UTexture2D* Texture_NonSelectedButtonImage_Normal;
	UTexture2D* Texture_NonSelectedButtonImage_HOvered;
	UTexture2D* Texture_NonSelectedButtonImage_Pressed;
	UTexture2D* Texture_AttackIconImage;
	UTexture2D* Texture_ArmorIconImage;

	//건물 기본 머티리얼
	UMaterialInterface* BasicMat_Barracks;
	UMaterialInterface* BasicMat_SynBioLab;
	UMaterialInterface* BasicMat_ResourceFacility;
	UMaterialInterface* BasicMat_EnergyRepeater;

	//건물 위치 지정 머티리얼
	UMaterialInterface* BuildEnableMat;
	UMaterialInterface* BuildDisableMat;

	//건물 메쉬
	UStaticMesh* StaticMesh_ResourceFacility;
	UStaticMesh* StaticMesh_Steelworks;
	UStaticMesh* StaticMesh_SynBioLab;
	UStaticMesh* StaticMesh_Temple;
	/*UStaticMeshComponent* StaticMesh_Barracks;*/

	//건물 클래스
	//UPROPERTY()
	//TSubclassOf<ABuilding_Barracks> Building_Barracks;

	//필요한 오브젝트 리턴
	UMaterial* GetMaterial(ESpawnObject SpawnObject);
	UTexture2D* GetTexture2D(uint8 Type);
	UStaticMesh* GetBuildingStaticMesh(uint8 Type);

private:
	UDataTable* UnitDataTable;
	UDataTable* BuildingDataTable;
	UDataTable* UpgradeDataTable;
};
