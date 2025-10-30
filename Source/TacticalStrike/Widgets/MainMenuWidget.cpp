// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/MainMenuController.h"
#include "OptionSettingsWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameButton = Cast<UButton>(GetWidgetFromName(TEXT("NewGameButton")));
	LoadGameButton = Cast<UButton>(GetWidgetFromName(TEXT("LoadGameButton")));
	OptionsButton = Cast<UButton>(GetWidgetFromName(TEXT("OptionsButton")));
	CreditsButton = Cast<UButton>(GetWidgetFromName(TEXT("CreditsButton")));
	ExitGameButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitGameButton")));

	OptionSettginsWidget = Cast<UOptionSettingsWidget>(GetWidgetFromName(TEXT("BP_OptionSettingsWidget")));

	if (NewGameButton != nullptr)
		NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGameButton_OnClicked);
	if (LoadGameButton != nullptr)
		LoadGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::LoadGameButton_OnClicked);
	if (OptionsButton != nullptr)
		OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OptionsButton_OnClicked);
	if (CreditsButton != nullptr)
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::CreditsButton_OnClicked);
	if (ExitGameButton != nullptr)
		ExitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGameButton_OnClicked);
}

void UMainMenuWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();
}

void UMainMenuWidget::SetMainMenu()
{
	if (StartAnimation)
		PlayAnimation(StartAnimation);
}

void UMainMenuWidget::NewGameButton_OnClicked()
{
	if (NewGameClickAnimation)
		PlayAnimation(NewGameClickAnimation);
	FTimerHandle NewGameTimerHandle;
	float NewGameTime = 2.0f;
	GetWorld()->GetTimerManager().SetTimer(NewGameTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("StrikeMap"), true);
		GetWorld()->GetTimerManager().ClearTimer(NewGameTimerHandle);
	}), NewGameTime, false);

}

void UMainMenuWidget::LoadGameButton_OnClicked()
{

}

void UMainMenuWidget::OptionsButton_OnClicked()
{

	if (OptionSettginsWidget != nullptr)
	{
		OptionSettginsWidget->SetVisibility(ESlateVisibility::Visible);
		OptionSettginsWidget->GraphicsButton_OnClicked();
	}
}

void UMainMenuWidget::CreditsButton_OnClicked()
{

}

void UMainMenuWidget::ExitGameButton_OnClicked()
{
	AMainMenuController* MainMenuController = Cast<AMainMenuController>(GetWorld()->GetFirstPlayerController());
	if (MainMenuController != nullptr)
		MainMenuController->ConsoleCommand("quit");

}