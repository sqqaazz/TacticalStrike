// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "MainOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UMainOptionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	class UButton* PauseButton;
	class UButton* SettingsButton;
	class UButton* BackToMenuButton;
	class UButton* ExitGameButton;
	class UButton* CloseButton;

	class UBorder* OptionsBorder;

	class UOptionSettingsWidget* OptionSettingsWidget;

private:

	UFUNCTION()
	void PauseButton_OnClicked();
	UFUNCTION()
	void SettingsButton_OnClicked();
	UFUNCTION()
	void BackToMenuButton_OnClicked();
	UFUNCTION()
	void ExitGameButton_OnClicked();
	UFUNCTION()
	void CloseButton_OnClicked();

	bool IsPaused;
};
