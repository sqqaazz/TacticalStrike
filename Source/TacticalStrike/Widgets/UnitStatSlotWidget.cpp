// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitStatSlotWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UnitStatTooltipWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UUnitStatSlotWidget::UUnitStatSlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUnitStatTooltipWidget> STATTOOLTIPWIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/Widgets/BP_UnitStatTooltipWidget.BP_UnitStatTooltipWidget_C'"));
	if (STATTOOLTIPWIDGET.Succeeded())
	{
		UnitStatTooltipWidgetClass = STATTOOLTIPWIDGET.Class;
	}
}

void UUnitStatSlotWidget::NativeConstruct()
{
	UnitStatImage = Cast<UImage>(GetWidgetFromName(TEXT("UnitStatImage")));
	UpgradeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UpgradeText")));

	UnitStatTooltipWidget = Cast<UUnitStatTooltipWidget>(CreateWidget(GetWorld(), UnitStatTooltipWidgetClass));
	if (UnitStatTooltipWidget != nullptr)
	{

		UnitStatTooltipWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		this->SetToolTip(UnitStatTooltipWidget);
	}
}

void UUnitStatSlotWidget::SetUnitStatTooltip(FString StatType, int32 DefaultStat, int32 UpgradeStat)
{
	UnitStatTooltipWidget->SetStatTooltip(StatType, DefaultStat, UpgradeStat);
}

void UUnitStatSlotWidget::SetStatImage(UTexture2D* StatTexture)
{
	if (StatTexture != nullptr)
		UnitStatImage->SetBrushFromTexture(StatTexture);
}