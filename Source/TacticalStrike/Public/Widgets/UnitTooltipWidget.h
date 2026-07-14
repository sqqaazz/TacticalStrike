// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/UnitDataTables.h"
#include "UnitTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UUnitTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	class UImage* UnitTooltipImage;
	class UTextBlock* UnitTooltipNameText;
	class UTextBlock* UnitTooltipAttackText;
	class UTextBlock* UnitTooltipArmorText;
	class UTextBlock* UnitTooltipCostText;
	class UTextBlock* UnitTooltipTechText;

	void ChangeTooltip(uint8 Type);

private:
	class UTacticalStrikeGameInstance* GameInstance;
	FUnitTableRow* UnitDataInfo;
};
