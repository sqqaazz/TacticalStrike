// Fill out your copyright notice in the Description page of Project Settings.


#include "MainOptionWidget.h"
#include "OptionSettingsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/CommanderController.h"

void UMainOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PauseButton = Cast<UButton>(GetWidgetFromName(TEXT("PauseButton")));
	SettingsButton = Cast<UButton>(GetWidgetFromName(TEXT("SettingsButton")));
	BackToMenuButton = Cast<UButton>(GetWidgetFromName(TEXT("BackToMenuButton")));
	ExitGameButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitGameButton")));
	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	OptionsBorder = Cast<UBorder>(GetWidgetFromName(TEXT("OptionsBorder")));

	OptionSettingsWidget = Cast<UOptionSettingsWidget>(GetWidgetFromName(TEXT("BP_OptionSettingsWidget")));

	PauseButton->OnClicked.AddDynamic(this, &UMainOptionWidget::PauseButton_OnClicked);
	SettingsButton->OnClicked.AddDynamic(this, &UMainOptionWidget::SettingsButton_OnClicked);
	BackToMenuButton->OnClicked.AddDynamic(this, &UMainOptionWidget::BackToMenuButton_OnClicked);
	ExitGameButton->OnClicked.AddDynamic(this, &UMainOptionWidget::ExitGameButton_OnClicked);
	CloseButton->OnClicked.AddDynamic(this, &UMainOptionWidget::CloseButton_OnClicked);

	OptionSettingsWidget->SetVisibility(ESlateVisibility::Collapsed);

	IsPaused = false;
}

void UMainOptionWidget::PauseButton_OnClicked()
{
	ACommanderController* CommanderController = Cast<ACommanderController>(GetWorld()->GetFirstPlayerController());
	if (CommanderController != nullptr)
	{
		if (IsPaused == false)
		{
			CommanderController->SetPause(true);
			IsPaused = true;
		}
		else
		{
			CommanderController->SetPause(false);
			IsPaused = false;
		}
	}
}

void UMainOptionWidget::SettingsButton_OnClicked()
{
	OptionSettingsWidget->SetVisibility(ESlateVisibility::Visible);
	OptionsBorder->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainOptionWidget::BackToMenuButton_OnClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartLevel"), true);
}

void UMainOptionWidget::ExitGameButton_OnClicked()
{
	ACommanderController* CommanderController = Cast<ACommanderController>(GetWorld()->GetFirstPlayerController());
	if (CommanderController != nullptr)
		CommanderController->ConsoleCommand("quit");
}

void UMainOptionWidget::CloseButton_OnClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);

}
