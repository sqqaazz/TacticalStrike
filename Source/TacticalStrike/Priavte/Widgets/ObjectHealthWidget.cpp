// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ObjectHealthWidget.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/ProgressBar.h"

void UObjectHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPProgressbar")));
	UpdateHealthWidget(nullptr);
}
//HP비율 업데이트
void UObjectHealthWidget::UpdateHealthWidget(ADefaultBuilding* ClickedDefaultBuilding)
{
	//UE_LOG(LogTemp, Log, TEXT("ssssssddddd"));
	if (nullptr != HPProgressBar && CurrentBuildingStat.IsValid())
	{
		float HPRatio = CurrentBuildingStat->GetHealthRatio();
		HPProgressBar->SetPercent(HPRatio);

		if (HPRatio < 0.3f)
			HPProgressBar->SetFillColorAndOpacity(FColor::Red);
		else if (HPRatio < 0.6f)
			HPProgressBar->SetFillColorAndOpacity(FColor::Orange);
		else
			HPProgressBar->SetFillColorAndOpacity(FColor::Green);

	}
}

void UObjectHealthWidget::BindBuildingWidget(ADefaultBuilding* NewBuildingStat)
{
	CurrentBuildingStat = NewBuildingStat;
	NewBuildingStat->OnBuildingHPChanged.AddUObject(this, &UObjectHealthWidget::UpdateHealthWidget);
}