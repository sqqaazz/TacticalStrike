// Fill out your copyright notice in the Description page of Project Settings.


#include "ResearchWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UResearchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResearchingProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ResearchingProgressBar")));
	ResearchingTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ResearchingText")));

	//GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ResearchPercent = 0;
}

void UResearchWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ResearchingProgressBar->SetPercent(ResearchPercent);
}