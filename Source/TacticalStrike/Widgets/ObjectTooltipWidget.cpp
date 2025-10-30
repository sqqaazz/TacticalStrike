// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectTooltipWidget.h"
#include "UnitTooltipWidget.h"
#include "BuildingTooltipWidget.h"

void UObjectTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UnitTooltipWidget = Cast<UUnitTooltipWidget>(GetWidgetFromName(TEXT("BP_UnitTooltip")));
	BuildingTooltipWidget = Cast<UBuildingTooltipWidget>(GetWidgetFromName(TEXT("BP_BuildingTooltip")));

}

void UObjectTooltipWidget::SetUnitTooltip(uint8 Type)
{
	if (UnitTooltipWidget != nullptr && BuildingTooltipWidget != nullptr)
	{
		UnitTooltipWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		BuildingTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);

		UnitTooltipWidget->ChangeTooltip(Type);
	}
}

void UObjectTooltipWidget::SetBuildingTooltip(uint8 Type)
{
	if (UnitTooltipWidget != nullptr && BuildingTooltipWidget != nullptr)
	{
		UnitTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
		BuildingTooltipWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		BuildingTooltipWidget->ChangeTooltip(Type);
	}
}

void UObjectTooltipWidget::SetEmpty()
{
	if (UnitTooltipWidget != nullptr && BuildingTooltipWidget != nullptr)
	{
		UnitTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
		BuildingTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
