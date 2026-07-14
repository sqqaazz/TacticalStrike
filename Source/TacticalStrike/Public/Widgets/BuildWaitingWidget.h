// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandSlotsWidget.h"
#include "DataTables/UnitDataTables.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "BuildWaitingWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBuildWaitingWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:

	TArray<UCommandSlotsWidget*> WaitingSlotsArr;

	void SetWaitingSlots(TArray<FObjectInfo> UnitDataArray);

	void SetBuildingSlotsMat(UCommandSlotsWidget* TargetSlot, UMaterial* Texture2D);
	void SetBuildingSlotsTexture(UCommandSlotsWidget* TargetSlot, UTexture2D* Texture2D);

	float BuildPercent;

	void UpdateBuildTime(int32 CurrentTime, int32 BuildingTime);

private:
	class UProgressBar* BuildingProgressBar;
	class UTextBlock* BuildingTextBlock;

	class UTacticalStrikeGameInstance* GameInstance;
};
