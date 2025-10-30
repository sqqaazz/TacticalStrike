// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/BuildingDataTables.h"
#include "BuildingTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBuildingTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	class UTextBlock* BuildingNameText;
	class UTextBlock* MineralText;
	class UTextBlock* TechText;
	class UTextBlock* InfoText;
	class UImage* BuildingImage;

	void ChangeTooltip(uint8 Type);

private:
	class UTacticalStrikeGameInstance* GameInstance;
	FBuildingTableRow* BuildingDataInfo;
};
