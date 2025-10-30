// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitStatSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UUnitStatSlotWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	UUnitStatSlotWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	class UImage* UnitStatImage;
	class UTextBlock* UpgradeText;

	void SetStatImage(UTexture2D* StatTexture);
	

	//½ºÅÈ ÅøÆÁ °ü·Ã
	class UUnitStatTooltipWidget* UnitStatTooltipWidget;
	TSubclassOf<class UUnitStatTooltipWidget> UnitStatTooltipWidgetClass;
	void SetUnitStatTooltip(FString StatType, int32 DefaultStat, int32 UpgradeStat);

//private:
//	class UTacticalStrikeGameInstance* GameInstance;
};
