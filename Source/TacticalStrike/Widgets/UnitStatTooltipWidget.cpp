// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitStatTooltipWidget.h"
#include "Components/TextBlock.h"

void UUnitStatTooltipWidget::NativeConstruct()
{
	StatTypeTitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("StatTypeTitleText")));
	DefaultStatText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DefaultStatText")));
	UpgradeStatText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UpgradeStatText")));
	StatTypeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("StatTypeText")));
}

void UUnitStatTooltipWidget::SetStatTooltip(FString StatType, int32 DefaultStat, int32 UpgradeStat)
{
	FString DefaultStatString = FString::Printf(TEXT("%d"), DefaultStat);
	FString UpgradeStatString = FString::Printf(TEXT("%d"), UpgradeStat);

	if (StatTypeTitleText != nullptr)
		StatTypeTitleText->SetText(FText::FromString(StatType));
	if (DefaultStatText != nullptr)
		DefaultStatText->SetText(FText::FromString(DefaultStatString));
	if (UpgradeStatText != nullptr)
		UpgradeStatText->SetText(FText::FromString(UpgradeStatString));
	if (StatTypeText != nullptr)
	{
		if (StatType == "Attack")
		{
			FString StatTypeString = FString::Printf(TEXT("Damage"));
			StatTypeText->SetText(FText::FromString(StatTypeString));
		}
		else if (StatType == "Armor")
		{
			FString StatTypeString = FString::Printf(TEXT("Damage Reduce"));
			StatTypeText->SetText(FText::FromString(StatTypeString));
		}
	}
}