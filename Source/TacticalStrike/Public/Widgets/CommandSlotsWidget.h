// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "CommandSlotsWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UCommandSlotsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UCommandSlotsWidget(const FObjectInitializer& ObjectInitializer);

protected:	
	virtual void NativeConstruct() override;

public:
	class UImage* BuildingBackgroundImage;
	class UButton* BuildingButton;
	class UImage* BuildingIconTexture;

	//오브젝트 툴팁 관련
	//class UUnitTooltipWidget* UnitTooltipWidget;
	//TSubclassOf<class UUnitTooltipWidget> UnitTooltipWidgetClass;

	//class UBuildingTooltipWidget* BuildingTooltipWidget;
	//TSubclassOf<class UBuildingTooltipWidget> BuildingTooltipWidgetClass;

	class UObjectTooltipWidget* ObjectTooltipWidget;
	TSubclassOf<class UObjectTooltipWidget> ObjectTooltipWidgetClass;

	void SetObjectType(uint8 Type);
	/*void SetUnitType(uint8 Type);*/
	//void SetBuildingType(uint8 Type);
	void UpdateTooltip(uint8 Type);

	//슬롯 조작 함수
	//void SetDefaultSlot(UMaterial* TargetMaterial);
	void SetSlotImageTexture2D(UTexture2D* TargetTexture);
	void SetSlotImageMat(UMaterial* TargetMaterial);

	//UPROPERTY(EditAnywhere, Category = "Details")
	//FString ObjectName;

	//UPROPERTY(EditAnywhere, Category = "Details")
	//FString Description;

};
