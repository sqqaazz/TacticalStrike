// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderBaseWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameMode/TacticalStrikeGameStateBase.h"
#include "CommandWidget.h"
//#include "UnitInfoWidget.h"
#include "MainOptionWidget.h"
#include "ResourceWidget.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UCommanderBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//TimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Timer")));
	TurnText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TurnText")));
	MessageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MessageText")));

	//자식 위젯 바인딩
	CommandWidget = Cast<UCommandWidget>(GetWidgetFromName(TEXT("BP_CommandWidget")));
	ObjectInfoWidget = Cast<UObjectInfoWidget>(GetWidgetFromName(TEXT("BP_ObjectInfoWidget")));
	ResourceWidget = Cast<UResourceWidget>(GetWidgetFromName(TEXT("BP_ResourceWidget")));
	MainOptionWidget = Cast<UMainOptionWidget>(GetWidgetFromName(TEXT("BP_MainOptionWidget")));
	//옵션 버튼 바인딩
	OptionOpenButton = Cast<UButton>(GetWidgetFromName(TEXT("OptionOpenButton")));
	if (OptionOpenButton != nullptr)
		OptionOpenButton->OnClicked.AddDynamic(this, &UCommanderBaseWidget::OptionOpenButton_OnClicked);

	TurnControlButton = Cast<UButton>(GetWidgetFromName(TEXT("TurnControlButton")));
	if (TurnControlButton != nullptr)
		TurnControlButton->OnClicked.AddDynamic(this, &UCommanderBaseWidget::TurnControlButton_OnClicked);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CommanderController = Cast<ACommanderController>(Cast<APlayerController>(GetOwningPlayerPawn()->GetController()));

	CommandWidget->SetBaseSlots();

	//GetWorldCommanderTimer = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	//if (GetWorldCommanderTimer != nullptr)
	//{
	//	GetWorldCommanderTimer->WorldCommanderTimer.AddDynamic(this, &UCommanderBaseWidget::UpdateWorldTimer);
	//}

	GetWorldCommanderTimer = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	if (GetWorldCommanderTimer != nullptr)
	{
		GetWorldCommanderTimer->PlayerTurnStartAfterDelegate.AddDynamic(this, &UCommanderBaseWidget::UpdateTurn);
	}
}

//void UCommanderBaseWidget::SetDefaultWidget()
//{
//	CommandWidget->SetBaseSlots();
//	ObjectInfoWidget->SetDefaultInfo();
//}

void UCommanderBaseWidget::SetWidgetState(FObjectInfo ObjectInfo)
{
	CommandWidget->SetCommandWidgetState(ObjectInfo);
	ObjectInfoWidget->ObjectTypeInfo(ObjectInfo);
	//UE_LOG(LogTemp, Log, TEXT("%d"), ObjectInfo.ObjectState);
}


//void UCommanderBaseWidget::UpdateWorldTimer()
//{
//	int32 TimeSecond = GetWorldCommanderTimer->CooldownTime;
//	FString SetTimerCount;
//	if (TimeSecond < 10)
//	{
//		SetTimerCount = FString::Printf(TEXT("00:0%d"), TimeSecond);
//	}
//	else
//	{
//		SetTimerCount = FString::Printf(TEXT("00:%d"), TimeSecond);
//	}
//
//	if (TimeText != nullptr)
//	{
//		TimeText->SetText(FText::FromString(SetTimerCount));
//	}
//}

void UCommanderBaseWidget::UpdateTurn()
{
	int32 Turn = 0;
	FString TurnTextStr;
	if (GetWorldCommanderTimer != nullptr)
	{
		Turn = GetWorldCommanderTimer->Turn;
	}
	TurnTextStr = FString::Printf(TEXT("Turn %d"), Turn);
	TurnText->SetText(FText::FromString(TurnTextStr));

	FObjectInfo ObjectInfo(0, 0, EObjectState::None, 0, 0, EObjectOwner::None, 0, nullptr);
	SetWidgetState(ObjectInfo);
}

void UCommanderBaseWidget::OptionOpenButton_OnClicked()
{
	MainOptionWidget->SetVisibility(ESlateVisibility::Visible);
	CommandWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCommanderBaseWidget::TurnControlButton_OnClicked()
{
	if (GetWorldCommanderTimer != nullptr)
	{
		GetWorldCommanderTimer->AITurnStart();
	}
}


void UCommanderBaseWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	CommanderController->IsEnterWidget();
}

void UCommanderBaseWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	CommanderController->IsNotEnterWidget();
}

//void UCommanderBaseWidget::SetUnitInfo(uint8 Type)
//{
//	ObjectInfoWidget->ObjectTypeInfo(Type);
//}

void UCommanderBaseWidget::UpdateObjectInfo(FObjectInfo ObjectInfo)
{
	//UE_LOG(LogTemp, Log, TEXT("UPDateBaseWidget: %d, %d"), Type, ChangeHP);
	ObjectInfoWidget->UpdateObjectInfo(ObjectInfo);
}

void UCommanderBaseWidget::ObjectBuildingInfo(FObjectInfo ObjectInfo)
{
	if (ObjectInfoWidget != nullptr)
	{
		//if (DataArrayNum == 0)
		//	ObjectInfoWidget->SetBuildingZeroArr(ObjectInfo);
		//else
		//	
		//UE_LOG(LogTemp, Log, TEXT("%d"), ObjectInfo.ObjectType);
		ObjectInfoWidget->SetBuildingInfo(ObjectInfo);
	}
}