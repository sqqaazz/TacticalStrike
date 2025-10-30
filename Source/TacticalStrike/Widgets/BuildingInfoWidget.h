// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildWaitingWidget.h"
#include "Controllers/CommanderController.h"
#include "BuildingInfoWidget.generated.h"

UCLASS()
class TACTICALSTRIKE_API UBuildingInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;

public:

	class UImage* BuildingInfoImage;
	class UTextBlock* BuildingNameText;
	class UTextBlock* CurrentHPText;
	class UTextBlock* DefaultHPText;
	class UTextBlock* DivideText;
	class UBuildWaitingWidget* BuildWaitingWidget;
	class UResearchWidget* ResearchWidget;
	class UBuildingTimeWidget* BuildingTimeWidget;
	class UVerticalBox* InfoVerticalBox;

	void SetBuildingInfo(FString BuildingName, UMaterial* BuildingInfoMaterial, int32 Attack, int32 Armor, int32 DefaultHP, int32 CurrentHP);

	//위젯 상태 조절
	void SetBuildingInfoState(FObjectInfo ObjectInfo);

	void SetBuildWaitingInfo();
	void EnableBuildWaitingInfo(FObjectInfo ObjectInfo);
	void DisableBuildWaitingInfo();
	void SetResearchInfo();
	void SetDefaultInfo();
	void SetBuildingDeActivatedInfo(FObjectInfo ObjectInfo);

	void ChangeBuildingCurrentHP();

private:
	class UTacticalStrikeGameInstance* GameInstance;
	class ACommanderController* CommanderController;
};
