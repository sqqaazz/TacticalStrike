// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitStatTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UUnitStatTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	class UTextBlock* StatTypeTitleText;
	class UTextBlock* DefaultStatText;
	class UTextBlock* UpgradeStatText;
	class UTextBlock* StatTypeText;

public:
	void SetStatTooltip(FString StatType, int32 DefaultStat, int32 UpgradeStat);
};
