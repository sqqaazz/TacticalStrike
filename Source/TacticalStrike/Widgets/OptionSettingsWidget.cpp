// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionSettingsWidget.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UOptionSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GraphicsButton = Cast<UButton>(GetWidgetFromName(TEXT("GraphicsButton")));
	SoundsButton = Cast<UButton>(GetWidgetFromName(TEXT("SoundsButton")));
	ControlsButton = Cast<UButton>(GetWidgetFromName(TEXT("ControlsButton")));
	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	GraphicsButton->OnClicked.AddDynamic(this, &UOptionSettingsWidget::GraphicsButton_OnClicked);
	SoundsButton->OnClicked.AddDynamic(this, &UOptionSettingsWidget::SoundsButton_OnClicked);
	ControlsButton->OnClicked.AddDynamic(this, &UOptionSettingsWidget::ControlsButton_OnClicked);
	CloseButton->OnClicked.AddDynamic(this, &UOptionSettingsWidget::CloseButton_OnClicked);
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//SelectedMargin = FMargin(60.0f, 10.0f, -40.0f, 10.0f);
	//NonSelectedMargin = FMargin(10.0f, 10.0f, 10.0f, 10.0f);

	SelectedImage_Normal = GameInstance->Texture_SelectedButtonImage_Normal;
	SelectedImage_HOvered = GameInstance->Texture_SelectedButtonImage_HOvered;
	SelectedImage_Pressed = GameInstance->Texture_SelectedButtonImage_Pressed;

	NonSelectedImage_Normal = GameInstance->Texture_NonSelectedButtonImage_Normal;
	NonSelectedImage_HOvered = GameInstance->Texture_NonSelectedButtonImage_HOvered;
	NonSelectedImage_Pressed = GameInstance->Texture_NonSelectedButtonImage_Pressed;
}

void UOptionSettingsWidget::GraphicsButton_OnClicked()
{
	//SetButtonPadding(GraphicsButton, SelectedMargin);
	//SetButtonPadding(SoundsButton, NonSelectedMargin);
	//SetButtonPadding(ControlsButton, NonSelectedMargin);

	if (ButtonsDefaultAnimation)
		PlayAnimation(ButtonsDefaultAnimation);
	if (GraphicsButtonClickAnimation)
		PlayAnimation(GraphicsButtonClickAnimation);

	SetButtonImage(GraphicsButton, SelectedImage_Normal, SelectedImage_HOvered, SelectedImage_Pressed);
	SetButtonImage(SoundsButton, NonSelectedImage_Normal, NonSelectedImage_HOvered, NonSelectedImage_Pressed);
	SetButtonImage(ControlsButton, NonSelectedImage_Normal, NonSelectedImage_HOvered, NonSelectedImage_Pressed);

}

void UOptionSettingsWidget::SoundsButton_OnClicked()
{
	//SetButtonPadding(GraphicsButton, NonSelectedMargin);
	//SetButtonPadding(SoundsButton, SelectedMargin);
	//SetButtonPadding(ControlsButton, NonSelectedMargin);

	if (ButtonsDefaultAnimation)
		PlayAnimation(ButtonsDefaultAnimation);
	if (SoundsButtonClickAnimation)
		PlayAnimation(SoundsButtonClickAnimation);

	SetButtonImage(GraphicsButton, NonSelectedImage_Normal, NonSelectedImage_HOvered, NonSelectedImage_Pressed);
	SetButtonImage(SoundsButton, SelectedImage_Normal, SelectedImage_HOvered, SelectedImage_Pressed);
	SetButtonImage(ControlsButton, NonSelectedImage_Normal, NonSelectedImage_HOvered, NonSelectedImage_Pressed);
}

void UOptionSettingsWidget::ControlsButton_OnClicked()
{
	//SetButtonPadding(GraphicsButton, NonSelectedMargin);
	//SetButtonPadding(SoundsButton, NonSelectedMargin);
	//SetButtonPadding(ControlsButton, SelectedMargin);

	if (ButtonsDefaultAnimation)
		PlayAnimation(ButtonsDefaultAnimation);
	if (ControlsButtonClickAnimation)
		PlayAnimation(ControlsButtonClickAnimation);

	SetButtonImage(GraphicsButton, NonSelectedImage_Normal, NonSelectedImage_HOvered, NonSelectedImage_Pressed);
	SetButtonImage(SoundsButton, NonSelectedImage_Normal, NonSelectedImage_HOvered, NonSelectedImage_Pressed);
	SetButtonImage(ControlsButton, SelectedImage_Normal, SelectedImage_HOvered, SelectedImage_Pressed);
}

void UOptionSettingsWidget::CloseButton_OnClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

//선택, 미선택 패딩 설정
//void UOptionSettingsWidget::SetButtonPadding(UButton* TargetButton, FMargin NewPadding)
//{
//	ButtonStyles.Padding = NewPadding;
//
//	if (TargetButton)
//		TargetButton->WidgetStyle.SetNormalPadding(NewPadding);
//
//	TargetButton->WidgetStyle.PressedPadding = FMargin(100.0f, 100.0f, 100.0f, 100.0f);
//
//}

//선택, 미선택 이미지 설정
void UOptionSettingsWidget::SetButtonImage(UButton* TargetButton, UTexture2D* NewNormalImage, UTexture2D* NewHOveredImage, UTexture2D* NewPressedImage)
{
	if (TargetButton)
	{
		TargetButton->WidgetStyle.Normal.SetResourceObject(NewNormalImage);
		TargetButton->WidgetStyle.Hovered.SetResourceObject(NewHOveredImage);
		TargetButton->WidgetStyle.Pressed.SetResourceObject(NewPressedImage);
	}
}