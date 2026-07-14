// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UObjectTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	class UUnitTooltipWidget* UnitTooltipWidget;
	class UBuildingTooltipWidget* BuildingTooltipWidget;

	void SetUnitTooltip(uint8 Type);
	void SetBuildingTooltip(uint8 Type);
	void SetEmpty();
};
