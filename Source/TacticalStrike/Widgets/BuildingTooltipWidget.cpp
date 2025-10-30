// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingTooltipWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/TacticalStrikeGameInstance.h"


void UBuildingTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BuildingNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("BuildingNameText")));
	MineralText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MineralText")));
	TechText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TechText")));
	InfoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("InfoText")));
	BuildingImage = Cast<UImage>(GetWidgetFromName(TEXT("BuildingImage")));

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

}

void UBuildingTooltipWidget::ChangeTooltip(uint8 Type)
{
	FString TooltipString;
	if (GameInstance != nullptr)
	{
		BuildingDataInfo = GameInstance->GetBuildingTable(Type);
		if (BuildingDataInfo != nullptr)
		{
			if (BuildingImage != nullptr)
				BuildingImage->SetBrushFromMaterial(GameInstance->GetMaterial(static_cast<ESpawnObject>(Type)));

			TooltipString = FString::Printf(TEXT("%s"), *BuildingDataInfo->Name);
			if (BuildingNameText != nullptr)
				BuildingNameText->SetText(FText::FromString(TooltipString));

			TooltipString = FString::Printf(TEXT("%d"), BuildingDataInfo->Cost);
			if (MineralText != nullptr)
				MineralText->SetText(FText::FromString(TooltipString));

			TooltipString = FString::Printf(TEXT("%d"), BuildingDataInfo->Tech);
			if (TechText != nullptr)
				TechText->SetText(FText::FromString(TooltipString));
		}
	}
}