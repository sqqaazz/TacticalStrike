// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* StartAnimation;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* NewGameClickAnimation;

	UFUNCTION(BlueprintCallable)
	void SetMainMenu();
	
private:
	class UButton* NewGameButton;
	class UButton* LoadGameButton;
	class UButton* OptionsButton;
	class UButton* CreditsButton;
	class UButton* ExitGameButton;

	class UOptionSettingsWidget* OptionSettginsWidget;

	UFUNCTION()
	void NewGameButton_OnClicked();
	UFUNCTION()
	void LoadGameButton_OnClicked();
	UFUNCTION()
	void OptionsButton_OnClicked();
	UFUNCTION()
	void CreditsButton_OnClicked();
	UFUNCTION()
	void ExitGameButton_OnClicked();

};
