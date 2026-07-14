// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "OptionSettingsWidget.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FButtonStyles
{
	GENERATED_BODY()
	FButtonStyle ButtonStyle;
	FMargin Padding;

	UTexture2D* NormalImage;
	UTexture2D* HOveredImage;
	UTexture2D* PressedImage;

};

UCLASS()
class TACTICALSTRIKE_API UOptionSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	class UButton* GraphicsButton;
	class UButton* SoundsButton;
	class UButton* ControlsButton;

	class UButton* CloseButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* GraphicsButtonClickAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* SoundsButtonClickAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ControlsButtonClickAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ButtonsDefaultAnimation;

	//UWidgetAnimation* GraphicsAnimation;
	//UWidgetAnimation* SoundsAnimation;
	//UWidgetAnimation* ControlsAnimation;

	//버튼 클릭 함수
	UFUNCTION()
	void GraphicsButton_OnClicked();
	UFUNCTION()
	void SoundsButton_OnClicked();
	UFUNCTION()
	void ControlsButton_OnClicked();
	UFUNCTION()
	void CloseButton_OnClicked();
private:
	class UTacticalStrikeGameInstance* GameInstance;
	
	//패딩 조정 함수
	//FMargin SelectedMargin;
	//FMargin NonSelectedMargin;
	//void SetButtonPadding(UButton* TargetButton, FMargin NewPadding);

	//이미지 조정 함수
	void SetButtonImage(UButton* TargetButton, UTexture2D* NewNormalImage, UTexture2D* NewHOveredImage, UTexture2D* NewPressedImage);
	UTexture2D* SelectedImage_Normal;
	UTexture2D* SelectedImage_HOvered;
	UTexture2D* SelectedImage_Pressed;
	UTexture2D* NonSelectedImage_Normal;
	UTexture2D* NonSelectedImage_HOvered;
	UTexture2D* NonSelectedImage_Pressed;

	FButtonStyles ButtonStyles;
};