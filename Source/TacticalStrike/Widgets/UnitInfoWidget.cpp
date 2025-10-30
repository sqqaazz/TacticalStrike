// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitInfoWidget.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUnitInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UnitInfoImage = Cast<UImage>(GetWidgetFromName(TEXT("UnitImage")));
	UnitNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UnitNameText")));
	CurrentHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentHPText")));
	DefaultHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DefaultHPText")));
	DivideText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DivideText")));

	AttackStatSlotWidget = Cast<UUnitStatSlotWidget>(GetWidgetFromName(TEXT("BP_UnitStatSlotWidget_Attack")));
	ArmorStatSlotWidget = Cast<UUnitStatSlotWidget>(GetWidgetFromName(TEXT("BP_UnitStatSlotWidget_Armor")));

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UUnitInfoWidget::SetUnitInfo(FString UnitName, UMaterial* UnitInfoMaterial, int32 Attack, int32 Armor, int32 DefaultHP, int32 CurrentHP)
{
	//FString UnitNameString;
	FString UnitDefaultHPString;
	FString UnitCurrentHPString;
	//FString UnitAttackString;
	//FString UnitArmorString;

	//UnitNameString = FString::Printf(TEXT("%s"), *UnitName);
	UnitDefaultHPString = FString::Printf(TEXT("%d"), DefaultHP);
	UnitCurrentHPString = FString::Printf(TEXT("%d"), CurrentHP);
	//UnitAttackString = FString::Printf(TEXT("%d"), Attack);
	//UnitArmorString = FString::Printf(TEXT("%d"), Armor);

	UnitInfoImage->SetBrushFromMaterial(UnitInfoMaterial);

	if (UnitNameText != nullptr)
		UnitNameText->SetText(FText::FromString(UnitName));
	if (CurrentHPText != nullptr)
		CurrentHPText->SetText(FText::FromString(UnitCurrentHPString));
	if (DefaultHPText != nullptr)
		DefaultHPText->SetText(FText::FromString(UnitDefaultHPString));

	
		float HPPercent = (float)CurrentHP / (float)DefaultHP;



		FLinearColor NewColor;
		UE_LOG(LogTemp, Log, TEXT("CurrentHPPercent: %f"), HPPercent);
		if (HPPercent < 0.3f)
		{
			NewColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
			CurrentHPText->SetColorAndOpacity(NewColor);
			DivideText->SetColorAndOpacity(NewColor);
			DefaultHPText->SetColorAndOpacity(NewColor);
		}
		else if (HPPercent < 0.6f)
		{
			NewColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
			CurrentHPText->SetColorAndOpacity(NewColor);
			DivideText->SetColorAndOpacity(NewColor);
			DefaultHPText->SetColorAndOpacity(NewColor);
		}
		else
		{
			NewColor = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);
			CurrentHPText->SetColorAndOpacity(NewColor);
			DivideText->SetColorAndOpacity(NewColor);
			DefaultHPText->SetColorAndOpacity(NewColor);
		}

	AttackStatSlotWidget->SetUnitStatTooltip("Attack", Attack, 0);
	ArmorStatSlotWidget->SetUnitStatTooltip("Armor", Armor, 0);

	if (GameInstance != nullptr)
	{
		AttackStatSlotWidget->SetStatImage(GameInstance->Texture_AttackIconImage);
		ArmorStatSlotWidget->SetStatImage(GameInstance->Texture_ArmorIconImage);
	}
}
