// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandWidget.h"
#include "Controllers/CommanderController.h"
//#include "UnitInfoWidget.h"
#include "ObjectInfoWidget.h"
#include "Components/Button.h"
#include "CommanderBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UCommanderBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
private:
	//class UTextBlock* TimeText;
	class UTextBlock* TurnText;
	class ATacticalStrikeGameStateBase* GetWorldCommanderTimer;

	//UFUNCTION()
	//void UpdateWorldTimer();

	UFUNCTION()
	void UpdateTurn();

	//옵션 버튼 바인딩, 클릭 이벤트 함수
	class UButton* OptionOpenButton;

	class UButton* TurnControlButton;

	UFUNCTION()
	void OptionOpenButton_OnClicked();

	UFUNCTION()
	void TurnControlButton_OnClicked();

public:

	class UCommandWidget* CommandWidget;
	//class UUnitInfoWidget* ObjectInfoWidget;
	class UObjectInfoWidget* ObjectInfoWidget;
	class UResourceWidget* ResourceWidget;
	class UMainOptionWidget* MainOptionWidget;

	class UTextBlock* MessageText;

	void SetWidgetState(FObjectInfo ObjectInfo);

	//void SetBarracksWidget();
	//void SetDefaultWidget();

	class UTacticalStrikeGameInstance* GameInstance;

	class ACommanderController* CommanderController;

	//유닛 정보 표기를 위해 사용
	void SetUnitInfo(uint8 Type);
	void UpdateObjectInfo(FObjectInfo ObjectInfo);

	void ObjectBuildingInfo(FObjectInfo ObjectInfo);
};
