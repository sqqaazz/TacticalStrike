// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitStatSlotWidget.h"
#include "UnitInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UUnitInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:

	class UImage* UnitInfoImage;
	class UTextBlock* UnitNameText;
	class UTextBlock* CurrentHPText;
	class UTextBlock* DefaultHPText;
	class UTextBlock* DivideText;
	//class UMaterial* UnitMaterial;

	class UUnitStatSlotWidget* AttackStatSlotWidget;
	class UUnitStatSlotWidget* ArmorStatSlotWidget;

	void SetUnitInfo(FString UnitName, UMaterial* UnitInfoMaterial, int32 Attack, int32 Armor, int32 DefaultHP, int32 CurrentHP);

private:
	class UTacticalStrikeGameInstance* GameInstance;
};
