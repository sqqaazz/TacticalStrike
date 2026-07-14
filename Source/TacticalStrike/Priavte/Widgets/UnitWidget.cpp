// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UnitWidget.h"
#include "Components/ProgressBar.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"

void UUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPProgressBar")));
	UpdateHealthWidget(nullptr);

	//WidgetPawn->RifleManHPChanged.AddUObject(this, &UUnitWidget::UpdateHealthWidget);
}
//HP비율 업데이트
void UUnitWidget::UpdateHealthWidget(ADefaultUnit* ClickedDefaultUnit)
{

	if (nullptr != HPProgressBar && CurrentUnitStat.IsValid())
	{
		float HPRatio = CurrentUnitStat->GetHealthRatio();
		HPProgressBar->SetPercent(HPRatio);

		if (HPRatio < 0.3f)
			HPProgressBar->SetFillColorAndOpacity(FColor::Red);
		else if (HPRatio < 0.6f)
			HPProgressBar->SetFillColorAndOpacity(FColor::Orange);
		else
			HPProgressBar->SetFillColorAndOpacity(FColor::Green);

	}
}

//void UUnitWidget::BindRifleManWidget(ARifleMan* NewCharacterStat)
//{
//	CurrentCharacterStat = NewCharacterStat;
//	NewCharacterStat->RifleManHPChanged.AddUObject(this, &UUnitWidget::UpdateHealthWidget);
//}

void UUnitWidget::BindUnitWidget(ADefaultUnit* NewCharacterStat)
{
	CurrentUnitStat = NewCharacterStat;
	NewCharacterStat->OnUnitHPChanged.AddUObject(this, &UUnitWidget::UpdateHealthWidget);
}