// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitInfoWidget.h"
#include "BuildingInfoWidget.h"
#include "DataTables/UnitDataTables.h"
#include "DataTables/BuildingDataTables.h"
#include "Controllers/CommanderController.h"
#include "ObjectInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UObjectInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
public:
	class UImage* ObjectInfoImage;
	class UTextBlock* ObjectInfoTextBlock;
	class UUnitInfoWidget* UnitInfoWidget;
	class UBuildingInfoWidget* BuildingInfoWidget;

	void SetDefaultInfo();


	void SetObjectInfoImageMat(UMaterial* Texture2D);
	void SetObjectInfoImageTexture(UTexture2D* Texture2D);

	//오브젝트 정보 위젯 표기를 위해 사용
	void ObjectTypeInfo(FObjectInfo ObjectInfo);
	void SetBuildingInfo(FObjectInfo ObjectInfo);
	void SetUnitInfo(uint8 UnitType);

	void SetBuildingZeroArr(FObjectInfo ObjectInfo);

	void UpdateObjectInfo(FObjectInfo ObjectInfo);
	void UpdateBuildingInfo(FObjectInfo ObjectInfo);
	void UpdateUnitInfo(uint8 UnitType, int32 ChangeHP);

private:
	class UTacticalStrikeGameInstance* GameInstance;
	class ACommanderController* GetCommanderController;

	FUnitTableRow* UnitDataInfo;
	FBuildingTableRow* BuildingDataInfo;
};
