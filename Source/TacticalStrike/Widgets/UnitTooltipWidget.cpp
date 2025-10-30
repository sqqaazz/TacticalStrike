// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitTooltipWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/TacticalStrikeGameInstance.h"

void UUnitTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UnitTooltipImage = Cast<UImage>(GetWidgetFromName(TEXT("UnitTooltipImage")));
	UnitTooltipNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UnitTooltipName")));
	UnitTooltipAttackText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UnitTooltipAttack")));
	UnitTooltipArmorText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UnitTooltipArmor")));
	UnitTooltipCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UnitTooltipCost")));
	UnitTooltipTechText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UnitTooltipTech")));

	//FString TooltipString;
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	//if (GameInstance != nullptr && UnitType != 0)
	//{
	//	UnitDataInfo = GameInstance->GetUnitTable(UnitType);

	//	TooltipString = FString::Printf(TEXT("%s"), *UnitDataInfo->Name);
	//	UnitTooltipNameText->SetText(FText::FromString(TooltipString));

	//	TooltipString = FString::Printf(TEXT("%s"), *UnitDataInfo->AttackType);
	//	UnitTooltipAttackText->SetText(FText::FromString(TooltipString));

	//	TooltipString = FString::Printf(TEXT("%s"), *UnitDataInfo->ArmorType);
	//	UnitTooltipArmorText->SetText(FText::FromString(TooltipString));

	//	TooltipString = FString::Printf(TEXT("%d"), UnitDataInfo->Cost);
	//	UnitTooltipCostText->SetText(FText::FromString(TooltipString));

	//	TooltipString = FString::Printf(TEXT("--"));
	//	UnitTooltipTechText->SetText(FText::FromString(TooltipString));

	//	UMaterial* ObjectMat = GameInstance->GetMaterial(UnitType);
	//	if (ObjectMat != nullptr)
	//		UnitTooltipImage->SetBrushFromMaterial(ObjectMat);
	//}
	
}


void UUnitTooltipWidget::ChangeTooltip(uint8 Type)
{
	//UE_LOG(LogTemp, Log, TEXT("%d"), UnitType);
	FString TooltipString;

	if (GameInstance != nullptr)
	{
		UnitDataInfo = GameInstance->GetUnitTable(Type);

		if (UnitDataInfo != nullptr)
		{
			TooltipString = FString::Printf(TEXT("%s"), *UnitDataInfo->Name);
			UnitTooltipNameText->SetText(FText::FromString(TooltipString));

			TooltipString = FString::Printf(TEXT("%s"), *UnitDataInfo->AttackType);
			UnitTooltipAttackText->SetText(FText::FromString(TooltipString));

			TooltipString = FString::Printf(TEXT("%s"), *UnitDataInfo->ArmorType);
			UnitTooltipArmorText->SetText(FText::FromString(TooltipString));

			TooltipString = FString::Printf(TEXT("%d"), UnitDataInfo->Cost);
			UnitTooltipCostText->SetText(FText::FromString(TooltipString));

			TooltipString = FString::Printf(TEXT("--"));
			UnitTooltipTechText->SetText(FText::FromString(TooltipString));

			UMaterial* ObjectMat = GameInstance->GetMaterial(static_cast<ESpawnObject>(Type));
			if (ObjectMat != nullptr)
				UnitTooltipImage->SetBrushFromMaterial(ObjectMat);
		}
	}
}