// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectInfoWidget.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UObjectInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UnitInfoWidget = Cast<UUnitInfoWidget>(GetWidgetFromName(TEXT("BP_UnitInfoWidget")));
	BuildingInfoWidget = Cast<UBuildingInfoWidget>(GetWidgetFromName(TEXT("BP_BuildingInfoWidget")));

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	SetDefaultInfo();
}

void UObjectInfoWidget::SetDefaultInfo()
{
	UnitInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	BuildingInfoWidget->SetVisibility(ESlateVisibility::Collapsed);

}

void UObjectInfoWidget::ObjectTypeInfo(FObjectInfo ObjectInfo)
{
	if (ObjectInfo.ObjectType == 0)
		SetDefaultInfo();
	else if (ObjectInfo.ObjectType < 100)
		SetUnitInfo(ObjectInfo.ObjectType);
	else if (ObjectInfo.ObjectType >= 100)
		SetBuildingInfo(ObjectInfo);
}

void UObjectInfoWidget::UpdateObjectInfo(FObjectInfo ObjectInfo)
{
	//UE_LOG(LogTemp, Log, TEXT("Type: %d, HP: %d"), Type, ChangeHP);
	if (ObjectInfo.ObjectType < 100)
		UpdateUnitInfo(ObjectInfo.ObjectType, ObjectInfo.CurrentHP);
	else if (ObjectInfo.ObjectType >= 100)
		UpdateBuildingInfo(ObjectInfo);
}

void UObjectInfoWidget::SetBuildingInfo(FObjectInfo ObjectInfo)
{
	UnitInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	if (GameInstance != nullptr && BuildingInfoWidget != nullptr)
	{
		BuildingDataInfo = GameInstance->GetBuildingTable(ObjectInfo.ObjectType);
		if (BuildingDataInfo != nullptr)
		{
			FString BuildingName = BuildingDataInfo->Name;
			int32 Attack = BuildingDataInfo->Attack;
			int32 Armor = BuildingDataInfo->Armor;
			int32 DefaultHP = BuildingDataInfo->MaxHP;
			int32 CurrentHP = ObjectInfo.CurrentHP;
			int32 BuildTime = BuildingDataInfo->BuildTime;
			UMaterial* BuildingMaterial = GameInstance->GetMaterial(static_cast<ESpawnObject>(ObjectInfo.ObjectType));

			BuildingInfoWidget->SetBuildingInfo(BuildingName, BuildingMaterial, Attack, Armor, DefaultHP, DefaultHP);
		}
		BuildingInfoWidget->SetVisibility(ESlateVisibility::Visible);
		BuildingInfoWidget->SetBuildingInfoState(ObjectInfo);
	}
}

//void UObjectInfoWidget::SetBuildingZeroArr(FObjectInfo ObjectInfo)
//{
//	UnitInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
//	if (GameInstance != nullptr && BuildingInfoWidget != nullptr)
//	{
//		BuildingDataInfo = GameInstance->GetBuildingTable(ObjectInfo.ObjectType);
//		if (BuildingDataInfo != nullptr)
//		{
//			FString BuildingName = BuildingDataInfo->Name;
//			int32 Attack = BuildingDataInfo->Attack;
//			int32 Armor = BuildingDataInfo->Armor;
//			int32 DefaultHP = BuildingDataInfo->MaxHP;
//			UMaterial* BuildingMaterial = GameInstance->GetMaterial(static_cast<ESpawnObject>(ObjectInfo.ObjectType));
//
//			BuildingInfoWidget->SetBuildingInfo(BuildingName, BuildingMaterial, Attack, Armor, DefaultHP, DefaultHP);
//		}
//		BuildingInfoWidget->SetVisibility(ESlateVisibility::Visible);
//		//BuildingInfoWidget->EnableBuildWaitingInfo();
//	}
//}

void UObjectInfoWidget::SetUnitInfo(uint8 UnitType)
{
	//UE_LOG(LogTemp, Log, TEXT("SetUnitInfo@@@@@@@@@@@@@@@@@@@"));
	BuildingInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	//UE_LOG(LogTemp, Log, TEXT("Setting..................."));
	if (GameInstance != nullptr && UnitInfoWidget != nullptr)
	{
		UnitDataInfo = GameInstance->GetUnitTable(UnitType);
		//UE_LOG(LogTemp, Log, TEXT("SetUnitInfo@2222222222222222222222@@@@"));
		if (UnitDataInfo != nullptr)
		{
			FString UnitName = UnitDataInfo->Name;
			int32 Attack = UnitDataInfo->Attack;
			int32 Armor = UnitDataInfo->Armor;
			int32 DefaultHP = UnitDataInfo->MaxHP;
			UMaterial* UnitMaterial = GameInstance->GetMaterial(static_cast<ESpawnObject>(UnitType));

			UnitInfoWidget->SetUnitInfo(UnitName, UnitMaterial, Attack, Armor, DefaultHP, DefaultHP);
		}
		UnitInfoWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UObjectInfoWidget::UpdateBuildingInfo(FObjectInfo ObjectInfo)
{
	UnitInfoWidget->SetVisibility(ESlateVisibility::Collapsed);

	if (GameInstance != nullptr && BuildingInfoWidget != nullptr)
	{
		BuildingDataInfo = GameInstance->GetBuildingTable(ObjectInfo.ObjectType);
		if (BuildingDataInfo != nullptr)
		{
			FString BuildingName = BuildingDataInfo->Name;
			int32 Attack = BuildingDataInfo->Attack;
			int32 Armor = BuildingDataInfo->Armor;
			int32 DefaultHP = BuildingDataInfo->MaxHP;
			int32 CurrentBuildTime = ObjectInfo.CurrentBuildTime;
			UMaterial* BuildingMaterial = GameInstance->GetMaterial(static_cast<ESpawnObject>(ObjectInfo.ObjectType));

			BuildingInfoWidget->SetBuildingInfo(BuildingName, BuildingMaterial, Attack, Armor, DefaultHP, CurrentBuildTime);
		}
		BuildingInfoWidget->SetVisibility(ESlateVisibility::Visible);
		BuildingInfoWidget->SetBuildingInfoState(ObjectInfo);
	}
}

void UObjectInfoWidget::UpdateUnitInfo(uint8 UnitType, int32 ChangeHP)
{
	BuildingInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	if (GameInstance != nullptr && UnitInfoWidget != nullptr)
	{
		UnitDataInfo = GameInstance->GetUnitTable(UnitType);
		if (UnitDataInfo != nullptr)
		{
			FString UnitName = UnitDataInfo->Name;
			int32 Attack = UnitDataInfo->Attack;
			int32 Armor = UnitDataInfo->Armor;
			int32 DefaultHP = UnitDataInfo->MaxHP;
			UMaterial* UnitMaterial = GameInstance->GetMaterial(static_cast<ESpawnObject>(UnitType));

			UnitInfoWidget->SetUnitInfo(UnitName, UnitMaterial, Attack, Armor, DefaultHP, ChangeHP);
		}
		UnitInfoWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UObjectInfoWidget::SetObjectInfoImageMat(UMaterial* Texture2D)
{
	//ObjectInfoImage->SetBrushFromMaterial(Texture2D);
}

void UObjectInfoWidget::SetObjectInfoImageTexture(UTexture2D* Texture2D)
{
	//ObjectInfoImage->SetBrushFromTexture(Texture2D);
}