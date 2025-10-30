// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingInfoWidget.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/BuildingClickableComponent.h"
#include "ResearchWidget.h"
#include "BuildingTimeWidget.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/BuildingClickableComponent.h"

void UBuildingInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BuildingInfoImage = Cast<UImage>(GetWidgetFromName(TEXT("BuildingInfoImage")));
	BuildingNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("BuildingNameText")));
	CurrentHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentHPText")));
	DefaultHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DefaultHPText")));
	DivideText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DivideText")));
	InfoVerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("InfoVerticalBox")));

	BuildWaitingWidget = Cast<UBuildWaitingWidget>(GetWidgetFromName(TEXT("BP_BuildWaiting")));
	ResearchWidget = Cast<UResearchWidget>(GetWidgetFromName(TEXT("BP_ResearchWidget")));
	BuildingTimeWidget = Cast<UBuildingTimeWidget>(GetWidgetFromName(TEXT("BP_BuildingTimeWidget")));

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CommanderController = Cast<ACommanderController>(Cast<APlayerController>(GetOwningPlayerPawn()->GetController()));

	SetDefaultInfo();
}

void UBuildingInfoWidget::SetBuildingInfo(FString BuildingName, UMaterial* BuilidingInfoMaterial, int32 Attack, int32 Armor, int32 DefaultHP, int32 CurrentHP)
{
	FString BuildingDefaultHPString;
	FString BuildingCurrentHPString;
	if (DefaultHP == 0)
	{
		BuildingDefaultHPString = "-";
		BuildingCurrentHPString = "-";
	}
	else
	{
		BuildingDefaultHPString = FString::Printf(TEXT("%d"), DefaultHP);
		BuildingCurrentHPString = FString::Printf(TEXT("%d"), CurrentHP);
	}

	BuildingInfoImage->SetBrushFromMaterial(BuilidingInfoMaterial);

	if (BuildingNameText != nullptr)
		BuildingNameText->SetText(FText::FromString(BuildingName));
	if (CurrentHPText != nullptr)
		CurrentHPText->SetText(FText::FromString(BuildingCurrentHPString));
	if (DefaultHPText != nullptr)
		DefaultHPText->SetText(FText::FromString(BuildingDefaultHPString));

	if (DefaultHP != 0)
	{
		float HPPercent = (float)CurrentHP / (float)DefaultHP;
		FLinearColor NewColor;
		if (HPPercent < 0.3f)
		{
			NewColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
			CurrentHPText->SetColorAndOpacity(NewColor);
			DivideText->SetColorAndOpacity(NewColor);
			DefaultHPText->SetColorAndOpacity(NewColor);
		}
		else if (HPPercent < 0.6f)
		{
			NewColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
			CurrentHPText->SetColorAndOpacity(NewColor);
			DivideText->SetColorAndOpacity(NewColor);
			DefaultHPText->SetColorAndOpacity(NewColor);
		}
		else
		{
			NewColor = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);
			CurrentHPText->SetColorAndOpacity(NewColor);
			DivideText->SetColorAndOpacity(NewColor);
			DefaultHPText->SetColorAndOpacity(NewColor);
		}
	}

	BuildWaitingWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UBuildingInfoWidget::SetBuildingInfoState(FObjectInfo ObjectInfo)
{
	EObjectState ObjectState = ObjectInfo.ObjectState;
	switch (ObjectState)
	{
	case EObjectState::Activated:
		SetDefaultInfo();
		break;
	case EObjectState::BuildWaited:
		EnableBuildWaitingInfo(ObjectInfo);
		break;
	case EObjectState::Researched:
		SetResearchInfo();
		break;
	case EObjectState::DeActivated:
		SetBuildingDeActivatedInfo(ObjectInfo);
		break;
	default:
		break;
	}
}

//void UBuildingInfoWidget::SetBuildWaitingInfo()
//{
//	if (CommanderController != nullptr && CommanderController->BuildingClickableComponent != nullptr && InfoVerticalBox != nullptr &&
//		CommanderController->BuildingClickableComponent->UnitDataArray.Num() == 0)
//	{
//		InfoVerticalBox->SetVisibility(ESlateVisibility::Visible);
//		BuildWaitingWidget->SetVisibility(ESlateVisibility::Collapsed);
//		ResearchWidget->SetVisibility(ESlateVisibility::Collapsed);
//		BuildingTimeWidget->SetVisibility(ESlateVisibility::Collapsed);
//	}
//	else if (CommanderController != nullptr && CommanderController->BuildingClickableComponent != nullptr && InfoVerticalBox != nullptr &&
//		CommanderController->BuildingClickableComponent->UnitDataArray.Num() != 0)
//	{
//		InfoVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
//		BuildWaitingWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
//		ResearchWidget->SetVisibility(ESlateVisibility::Collapsed);
//		BuildingTimeWidget->SetVisibility(ESlateVisibility::Collapsed);
//	}
//
//
//}

void UBuildingInfoWidget::EnableBuildWaitingInfo(FObjectInfo ObjectInfo)
{
	if (CommanderController != nullptr && CommanderController->BuildingClickableComponent != nullptr && 
		InfoVerticalBox != nullptr && BuildWaitingWidget != nullptr && ResearchWidget != nullptr && BuildingTimeWidget != nullptr)
		{
			InfoVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
			BuildWaitingWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
			ResearchWidget->SetVisibility(ESlateVisibility::Collapsed);
			BuildingTimeWidget->SetVisibility(ESlateVisibility::Collapsed);

			ADefaultBuilding* DefaultBuilding = Cast<ADefaultBuilding>(ObjectInfo.ObjectActor);
			UBuildingClickableComponent* BuildingClickabltComponent = DefaultBuilding->ClickableComponent;
			if (BuildingClickabltComponent != nullptr)
			{
				BuildWaitingWidget->UpdateBuildTime(BuildingClickabltComponent->UnitDataArray[0].CurrentBuildTime, BuildingClickabltComponent->UnitDataArray[0].BuildTime);
				//UE_LOG(LogTemp, Log, TEXT("%d, %d"), BuildingClickabltComponent->UnitDataArray[0].CurrentBuildTime, BuildingClickabltComponent->UnitDataArray[0].BuildTime);
				BuildWaitingWidget->SetWaitingSlots(BuildingClickabltComponent->UnitDataArray);
			}
		}
}

//void UBuildingInfoWidget::DisableBuildWaitingInfo()
//{
//	if (InfoVerticalBox != nullptr && BuildWaitingWidget != nullptr && ResearchWidget && nullptr && BuildingTimeWidget != nullptr)
//	{
//		InfoVerticalBox->SetVisibility(ESlateVisibility::Visible);
//		BuildWaitingWidget->SetVisibility(ESlateVisibility::Collapsed);
//		ResearchWidget->SetVisibility(ESlateVisibility::Collapsed);
//		BuildingTimeWidget->SetVisibility(ESlateVisibility::Collapsed);
//
//	}
//}

void UBuildingInfoWidget::SetResearchInfo()
{
	if (InfoVerticalBox != nullptr && BuildWaitingWidget != nullptr && ResearchWidget != nullptr && BuildingTimeWidget != nullptr)
	{

		InfoVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
		BuildWaitingWidget->SetVisibility(ESlateVisibility::Collapsed);
		ResearchWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		BuildingTimeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBuildingInfoWidget::SetDefaultInfo()
{
	if (InfoVerticalBox != nullptr && BuildWaitingWidget != nullptr && ResearchWidget != nullptr && BuildingTimeWidget != nullptr)
	{
		InfoVerticalBox->SetVisibility(ESlateVisibility::Visible);
		BuildWaitingWidget->SetVisibility(ESlateVisibility::Collapsed);
		ResearchWidget->SetVisibility(ESlateVisibility::Collapsed);
		BuildingTimeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBuildingInfoWidget::SetBuildingDeActivatedInfo(FObjectInfo ObjectInfo)
{
	if (InfoVerticalBox != nullptr && BuildWaitingWidget != nullptr && ResearchWidget != nullptr && BuildingTimeWidget != nullptr)
	{
		InfoVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
		BuildWaitingWidget->SetVisibility(ESlateVisibility::Collapsed);
		ResearchWidget->SetVisibility(ESlateVisibility::Collapsed);
		BuildingTimeWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

		BuildingTimeWidget->UpdateBuildTime(ObjectInfo.CurrentBuildTime, ObjectInfo.BuildTime);
	}
}


void UBuildingInfoWidget::ChangeBuildingCurrentHP()
{
}