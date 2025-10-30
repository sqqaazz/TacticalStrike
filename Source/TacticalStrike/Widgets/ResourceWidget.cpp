// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"
#include "Components/TextBlock.h"
#include "Controllers/CommanderController.h"

void UResourceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MineralText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Mineral")));
	GasText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Gas")));

	PlayerController = Cast<ACommanderController>(GetOwningPlayer());
}

//void UResourceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//	Super::NativeTick(MyGeometry, InDeltaTime);
//
//	FString SetMineralCount;
//
//	if (MineralText != nullptr && PlayerController != nullptr)
//	{
//		SetMineralCount = FString::Printf(TEXT("%d"), FMath::RoundToInt(PlayerController->Mineral));
//		MineralText->SetText(FText::FromString(SetMineralCount));
//	}
//}

void UResourceWidget::UpdateResourceState()
{

}