// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticalStrikeGameInstance.h"
#include "DataTables/UnitDataTables.h"
#include "DataTables/BuildingDataTables.h"
#include "DataTables/UpgradeDataTables.h"

UTacticalStrikeGameInstance::UTacticalStrikeGameInstance()
{
	//데이터 테이블
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable_Unit(TEXT("DataTable'/Game/DataTable/unitDataTable.UnitDataTable'"));
	if (DataTable_Unit.Succeeded())
		UnitDataTable = DataTable_Unit.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable_Building(TEXT("DataTable'/Game/DataTable/BuildingDataTable.BuildingDataTable'"));
	if (DataTable_Building.Succeeded())
		BuildingDataTable = DataTable_Building.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable_Upgrade(TEXT("DataTable'/Game/DataTable/UpgradeDataTable.UpgradeDataTable'"));
	if (DataTable_Upgrade.Succeeded())
		UpgradeDataTable = DataTable_Upgrade.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> TransparencyTexture(TEXT("Material'/Game/Material/TransparencyMat.TransparencyMat'"));
	if (TransparencyTexture.Succeeded())
		Texture_Transparency = TransparencyTexture.Object;

	//유닛 이미지
	static ConstructorHelpers::FObjectFinder<UMaterial> RifleManTexture(TEXT("Material'/Game/2DTextures/RifleMan2D_Tex_Mat.RifleMan2D_Tex_Mat'"));
	if (RifleManTexture.Succeeded())
	{
		Texture_RifleMan = RifleManTexture.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> SwordManTexture(TEXT("Material'/Game/2DTextures/UnitTexture/SwordMan2D_Tex_Mat.SwordMan2D_Tex_Mat'"));
	if (SwordManTexture.Succeeded())
	{
		Texture_SwordMan = SwordManTexture.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MutantTexture(TEXT("Material'/Game/2DTextures/UnitTexture/Mutant2D_Tex_Mat.Mutant2D_Tex_Mat'"));
	if (RifleManTexture.Succeeded())
	{
		Texture_Mutant = MutantTexture.Object;
	}

	//건물, 건설 이미지
	static ConstructorHelpers::FObjectFinder<UTexture2D> BuildIconTexture(TEXT("Texture2D'/Game/CraftResourcesIcons/Textures/Tex_tools_07_b.Tex_tools_07_b'"));
	if (BuildIconTexture.Succeeded())
	{
		Texture_BuildIcon = BuildIconTexture.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> TechIconTexture(TEXT("Texture2D'/Game/CraftResourcesIcons/Textures/Tex_tools_03_b.Tex_tools_03_b'"));
	if (TechIconTexture.Succeeded())
	{
		Texture_TechIcon = TechIconTexture.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> EmptyTexture(TEXT("Texture2D'/Game/RunesSystem/Textures/T_RuneBackground.T_RuneBackground'"));
	if (EmptyTexture.Succeeded())
	{
		Texture_Empty = EmptyTexture.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> StopBuildingTexture(TEXT("Texture2D'/Game/RunesSystem/Textures/Shop/T_ShopClose.T_ShopClose'"));
	if (StopBuildingTexture.Succeeded())
	{
		Texture_StopBuilding = StopBuildingTexture.Object;
	}

	//건물 이미지
	static ConstructorHelpers::FObjectFinder<UMaterial> BarracksTexture(TEXT("Material'/Game/2DTextures/Barracks2D_Tex2_Mat.Barracks2D_Tex2_Mat'"));
	if (BarracksTexture.Succeeded())
		Texture_Barracks = BarracksTexture.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> SynBioLabTexture(TEXT("Material'/Game/2DTextures/BuildingTexture/SynBioLab_RenderTarget2D_Mat.SynBioLab_RenderTarget2D_Mat'"));
	if (SynBioLabTexture.Succeeded())
		Texture_SynBioLab = SynBioLabTexture.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> ResourceFacilityTexture(TEXT("Material'/Game/2DTextures/BuildingTexture/ResourceFacility_RanderTarget2D_Tex_Mat.ResourceFacility_RanderTarget2D_Tex_Mat'"));
	if (ResourceFacilityTexture.Succeeded())
		Texture_ResourceFacility = ResourceFacilityTexture.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> TampleTexture(TEXT("Material'/Game/2DTextures/BuildingTexture/Tample_Rander_Tex_Mat.Tample_Rander_Tex_Mat'"));
	if (TampleTexture.Succeeded())
		Texture_Tample = TampleTexture.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> EnergyRepeaterTexture(TEXT("/Script/Engine.Material'/Game/2DTextures/BuildingTexture/M_EnergyRepeater_RenderTarget.M_EnergyRepeater_RenderTarget'"));
	if (EnergyRepeaterTexture.Succeeded())
		Texture_EnergyRepeater = EnergyRepeaterTexture.Object;
	

	//업그레이드 이미지
	static ConstructorHelpers::FObjectFinder<UTexture2D> ResourceUpgradeTexture(TEXT("Texture2D'/Game/CraftResourcesIcons/Textures/Tex_gemstone_04.Tex_gemstone_04'"));
	if (ResourceUpgradeTexture.Succeeded())
		Texture_ResourceUpgrade = ResourceUpgradeTexture.Object;

	//UI 이미지
	static ConstructorHelpers::FObjectFinder<UTexture2D> SelectedButtonTexture_Normal(TEXT("Texture2D'/Game/2DTextures/Import/UI_Windows/Btn_V20.Btn_V20'"));
	if (SelectedButtonTexture_Normal.Succeeded())
		Texture_SelectedButtonImage_Normal = SelectedButtonTexture_Normal.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> SelectedButtonTexture_HOvered(TEXT("Texture2D'/Game/2DTextures/Import/UI_Windows/Btn_V20_HOvered.Btn_V20_HOvered'"));
	if (SelectedButtonTexture_HOvered.Succeeded())
		Texture_SelectedButtonImage_HOvered = SelectedButtonTexture_HOvered.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> SelectedButtonTexture_Pressed(TEXT("Texture2D'/Game/2DTextures/Import/UI_Windows/Btn_V20_Pressed.Btn_V20_Pressed'"));
	if (SelectedButtonTexture_Pressed.Succeeded())
		Texture_SelectedButtonImage_Pressed = SelectedButtonTexture_Pressed.Object;


	static ConstructorHelpers::FObjectFinder<UTexture2D> NonSelectedButtonTexture_Normal(TEXT("Texture2D'/Game/2DTextures/Import/UI_Windows/Window03_Btn.Window03_Btn'"));
	if (NonSelectedButtonTexture_Normal.Succeeded())
	{
		Texture_NonSelectedButtonImage_Normal = NonSelectedButtonTexture_Normal.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> NonSelectedButtonTexture_HOvered(TEXT("Texture2D'/Game/2DTextures/Import/UI_Windows/Window03_Btn_Hovered.Window03_Btn_Hovered'"));
	if (NonSelectedButtonTexture_HOvered.Succeeded())
	{
		Texture_NonSelectedButtonImage_HOvered = NonSelectedButtonTexture_HOvered.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> NonSelectedButtonTexture_Pressed(TEXT("Texture2D'/Game/2DTextures/Import/UI_Windows/Window03_Btn_Pressed.Window03_Btn_Pressed'"));
	if (NonSelectedButtonTexture_Pressed.Succeeded())
	{
		Texture_NonSelectedButtonImage_Pressed = NonSelectedButtonTexture_Pressed.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> AttackIconTexture(TEXT("Texture2D'/Game/2DTextures/Import/1__Free_Hologram_Interface_Wenrexa/Icons/17.17'"));
	if (AttackIconTexture.Succeeded())
	{
		Texture_AttackIconImage = AttackIconTexture.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> ArmorIconTexture(TEXT("Texture2D'/Game/2DTextures/Import/1__Free_Hologram_Interface_Wenrexa/Icons/18.18'"));
	if (ArmorIconTexture.Succeeded())
	{
		Texture_ArmorIconImage = ArmorIconTexture.Object;
	}

	//건물 위치 지정 머티리얼
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BuildEnable_Material(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Hologram_Green.MI_Hologram_Green'"));
	if (BuildEnable_Material.Succeeded())
	{
		BuildEnableMat = BuildEnable_Material.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BuildDisable_Material(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Hologram_Red.MI_Hologram_Red'"));
	if (BuildDisable_Material.Succeeded())
	{
		BuildDisableMat = BuildDisable_Material.Object;
	}

	//건물 기본 머티리얼
	static ConstructorHelpers::FObjectFinder<UMaterial> Basic_Material_Barracks(TEXT("Material'/Game/3DModels/StaticMesh/Buildings/Barracks/rts-military-building-1/textures/model/textures/build_material_albedo_Mat.build_material_albedo_Mat'"));
	if (Basic_Material_Barracks.Succeeded())
		BasicMat_Barracks = Basic_Material_Barracks.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> Basic_Material_SynBioLab(TEXT("Material'/Game/3DModels/Buildings/MRowaBuildings/jewelry-factory/source/Placeable_006.Placeable_006'"));
	if (Basic_Material_SynBioLab.Succeeded())
		BasicMat_SynBioLab = Basic_Material_SynBioLab.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> Basic_Material_ResourceFacility(TEXT("Material'/Game/3DModels/Buildings/MRowaBuildings/coal-power-station/source/CoalPowerStation/Placeable.Placeable'"));
	if (Basic_Material_ResourceFacility.Succeeded())
		BasicMat_ResourceFacility = Basic_Material_ResourceFacility.Object;
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Basic_Material_EnergyRepeater(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/HoverVehicles/Materials/LampPole/MAT_LampPole.MAT_LampPole'"));
	if (Basic_Material_EnergyRepeater.Succeeded())
		BasicMat_EnergyRepeater = Basic_Material_EnergyRepeater.Object;

	//건물 메쉬
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Building_ResourceFacility(TEXT("StaticMesh'/Game/3DModels/Buildings/MRowaBuildings/coal-power-station/source/CoalPowerStation/CoalPowerStation_Merge_CoalPowerStation_MainDoor.CoalPowerStation_Merge_CoalPowerStation_MainDoor'"));
	if (Building_ResourceFacility.Succeeded())
		StaticMesh_ResourceFacility = Building_ResourceFacility.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Building_SynBioLab(TEXT("StaticMesh'/Game/3DModels/Buildings/MRowaBuildings/jewelry-factory/source/JewelryFactory_Merge_JewelryFactory_Parts.JewelryFactory_Merge_JewelryFactory_Parts'"));
	if (Building_SynBioLab.Succeeded())
		StaticMesh_SynBioLab = Building_SynBioLab.Object;
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingBarracks(TEXT("StaticMesh'/Game/3DModels/StaticMesh/Buildings/Barracks/rts-military-building-1/SM_MERGED_Barracks_build_19.SM_MERGED_Barracks_build_19'"));
	//if (BuildingBarracks.Succeeded())
	//{
	//	StaticMesh_Barracks->SetStaticMesh(BuildingBarracks.Object);
	//}

	//건물 클래스
	//static ConstructorHelpers::FClassFinder<ABuilding_Barracks> Spawning_Barracks(TEXT("Class'/Script/TacticalStrike.Building_Barracks'"));
	//if (Spawning_Barracks.Succeeded())
	//{
	//	Building_Barracks = Spawning_Barracks.Class;
	//}
}

TArray<FUnitTableRow*> UTacticalStrikeGameInstance::GetAllUnitTable()
{
	TArray<FUnitTableRow*> UnitTable;
	UnitDataTable->GetAllRows<FUnitTableRow>(TEXT(""), UnitTable);
	return UnitTable;
}

FUnitTableRow* UTacticalStrikeGameInstance::GetUnitTable(int32 UnitType)
{
	return UnitDataTable->FindRow<FUnitTableRow>(*FString::FromInt(UnitType), TEXT(""));
}

FBuildingTableRow* UTacticalStrikeGameInstance::GetBuildingTable(int32 BuildingType)
{
	return BuildingDataTable->FindRow<FBuildingTableRow>(*FString::FromInt(BuildingType), TEXT(""));
}

FUpgradeTableRow* UTacticalStrikeGameInstance::GetUpgradeTable(int32 BuildingType)
{
	return UpgradeDataTable->FindRow<FUpgradeTableRow>(*FString::FromInt(BuildingType), TEXT(""));
}

UMaterial* UTacticalStrikeGameInstance::GetMaterial(ESpawnObject SpawnObject)
{
	switch (SpawnObject)
	{
	case ESpawnObject::RifleMan:
		return Texture_RifleMan;
	case ESpawnObject::SwordMan:
		return Texture_SwordMan;
	case ESpawnObject::Mutant:
		return Texture_Mutant;
	case ESpawnObject::Barracks:
		return Texture_Barracks;
	case ESpawnObject::SynBioLab:
		return Texture_SynBioLab;
	case ESpawnObject::EnergyRepeater:
		return Texture_EnergyRepeater;
	case ESpawnObject::Tample:
		return Texture_Tample;
	case ESpawnObject::ResourceFacility:
		return Texture_ResourceFacility;
	default:
		return nullptr;
	}
}

UTexture2D* UTacticalStrikeGameInstance::GetTexture2D(uint8 Type)
{
	switch (Type)
	{
	case 221:
		return Texture_ResourceUpgrade;
	default:
		return nullptr;
	}
}

UStaticMesh* UTacticalStrikeGameInstance::GetBuildingStaticMesh(uint8 Type)
{
	switch (Type)
	{
	case 102:
		return StaticMesh_SynBioLab;
	case 202:
		return StaticMesh_ResourceFacility;
	default:
		return nullptr;
	}
}