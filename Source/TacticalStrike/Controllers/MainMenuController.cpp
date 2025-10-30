// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuController.h"
#include "Widgets/MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Units/Mutant/Mutant.h"
#include "Characters/Units/RifleMan/RifleMan.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "GameFramework/GameUserSettings.h"

AMainMenuController::AMainMenuController()
{
	//static ConstructorHelpers::FClassFinder<UMainMenuWidget> MAINMENUWIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/BP_MainMenuWidget.BP_MainMenuWidget_C'"));
	//if (MAINMENUWIDGET.Succeeded())
	//	MainMenuWidgetClass = MAINMENUWIDGET.Class;
	
	SetShowMouseCursor(true);
}

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	FIntPoint Screen_FHD = (1280, 720);
	GameUserSettings->SetScreenResolution(Screen_FHD);
	GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);

	GameUserSettings->ApplySettings(false);

	//MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
	//MainMenuWidget->AddToViewport();
}

void AMainMenuController::StartSequence()
{
	TArray<AActor*> SequenceUnitArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultUnit::StaticClass(), SequenceUnitArr);

	for (int32 i = 0; i < SequenceUnitArr.Num(); i++)
	{
		ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(SequenceUnitArr[i]);
		if (DefaultUnit != nullptr)
		{
			ARifleMan* RifleMan = Cast<ARifleMan>(DefaultUnit);
			if (RifleMan != nullptr)
			{
				if (RifleMan->ActorHasTag("SequenceUnit"))
				{
					RifleMan->GetMesh()->SetVisibility(true);
					RifleMan->RifleMesh->SetVisibility(true);
				}
				else if (RifleMan->ActorHasTag("MainMenuUnit"))
				{
					RifleMan->GetMesh()->SetVisibility(false);
					RifleMan->RifleMesh->SetVisibility(false);
				}
			}
			else
			{
				if (DefaultUnit->ActorHasTag("SequenceUnit"))
					DefaultUnit->GetMesh()->SetVisibility(true);
				else if (DefaultUnit->ActorHasTag("MainMenuUnit"))
					DefaultUnit->GetMesh()->SetVisibility(false);
			}
		}
	}

}

void AMainMenuController::EndSequence()
{
	TArray<AActor*> SequenceUnitArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultUnit::StaticClass(), SequenceUnitArr);

	for (int32 i = 0; i < SequenceUnitArr.Num(); i++)
	{
		ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(SequenceUnitArr[i]);
		if (DefaultUnit != nullptr)
		{
			if (DefaultUnit->ActorHasTag("SequenceUnit"))
				DefaultUnit->GetMesh()->SetVisibility(false);
			else if (DefaultUnit->ActorHasTag("MainMenuUnit"))
				DefaultUnit->GetMesh()->SetVisibility(true);
		}
	}

}
