// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildWaitingWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBuildWaitingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WaitingSlotsArr.Emplace(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_0"))));
	WaitingSlotsArr.Emplace(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_1"))));
	WaitingSlotsArr.Emplace(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_2"))));
	WaitingSlotsArr.Emplace(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_3"))));
	WaitingSlotsArr.Emplace(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_4"))));

	BuildingProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BuildingProgressBar")));
	BuildingTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("BuildingText")));

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	BuildPercent = 0;

	//FUnitTableRow* TestData = GameInstance->GetUnitTable(1);
	//UE_LOG(LogTemp, Log, TEXT("%s"), *TestData->Name);
}

//void UBuildWaitingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//	Super::NativeTick(MyGeometry, InDeltaTime);
//
//	BuildingProgressBar->SetPercent(BuildPercent);
//	//UE_LOG(LogTemp, Log, TEXT("%f"), BuildPercent);
//}

void UBuildWaitingWidget::SetWaitingSlots(TArray<FObjectInfo> UnitDataArray)
{
	for (uint8 i = 0; i < UnitDataArray.Num(); i++)
	{
		WaitingSlotsArr[i]->BuildingIconTexture->SetVisibility(ESlateVisibility::HitTestInvisible);
		SetBuildingSlotsMat(WaitingSlotsArr[i], GameInstance->GetMaterial(static_cast<ESpawnObject>(UnitDataArray[i].ObjectType)));
	}
	for (uint8 i = UnitDataArray.Num(); i < 5; i++)
	{
		WaitingSlotsArr[i]->BuildingIconTexture->SetVisibility(ESlateVisibility::Collapsed);
		//SetBuildingSlotsTexture(WaitingSlotsArr[i], GameInstance->Texture_Empty);
	}
}

void UBuildWaitingWidget::UpdateBuildTime(int32 CurrentTime, int32 BuildingTime)
{
	//UE_LOG(LogTemp, Log, TEXT("%d, %d"), CurrentTime, BuildingTime);
	BuildingProgressBar->SetPercent(float(CurrentTime) / float(BuildingTime));
}

void UBuildWaitingWidget::SetBuildingSlotsMat(UCommandSlotsWidget* TargetSlot, UMaterial* Texture2D)
{
	TargetSlot->BuildingIconTexture->SetBrushFromMaterial(Texture2D);
}

void UBuildWaitingWidget::SetBuildingSlotsTexture(UCommandSlotsWidget* TargetSlot, UTexture2D* Texture2D)
{
	TargetSlot->BuildingIconTexture->SetBrushFromTexture(Texture2D);
}