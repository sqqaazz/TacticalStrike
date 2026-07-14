// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuildingTimeWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UBuildingTimeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BuildingTimeProgressbar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BuildingTimeProgressBar")));
	BuildingTimeTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("BuildingTimeText")));
	//ResearchPercent = 0;
}

//void UBuildingTimeWidget::SetProgressbar(int32 CurrentTime, int32 BuildingTime)
//{
//	BuildingTimeProgressbar->SetPercent(float(CurrentTime) / float(BuildingTime));
//}

void UBuildingTimeWidget::UpdateBuildTime(int32 CurrentTime, int32 BuildingTime)
{
	BuildingTimeProgressbar->SetPercent(float(CurrentTime) / float(BuildingTime));
}