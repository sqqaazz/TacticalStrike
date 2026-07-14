// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Controllers/CommanderController.h"
#include "CommandWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UCommandWidget : public UUserWidget
{
	GENERATED_BODY()
	
//public:
//	UCommandWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	//°¢ ½½·Ôµé
	UPROPERTY()
	TArray<class UCommandSlotsWidget*> BuildingSlotsArray;
	//class UCommandSlotsWidget* BuildingSlots_0;
	//class UCommandSlotsWidget* BuildingSlots_1;
	//class UCommandSlotsWidget* BuildingSlots_2;
	//class UCommandSlotsWidget* BuildingSlots_3;
	//class UCommandSlotsWidget* BuildingSlots_4;
	//class UCommandSlotsWidget* BuildingSlots_5;
	//class UCommandSlotsWidget* BuildingSlots_6;
	//class UCommandSlotsWidget* BuildingSlots_7;
	//class UCommandSlotsWidget* BuildingSlots_8;

	//class UUnitTooltipWidget* UnitTooltipWidget;

	//TSubclassOf<class UUnitTooltipWidget> UnitTooltipWidgetClass;

	class ACommanderController* GetCommanderController;

	void SetBuildingSlotsMat(class UCommandSlotsWidget* TargetSlot, UMaterial* Texture2D);
	void SetBuildingSlotsTexture(class UCommandSlotsWidget* TargetSlot, UTexture2D* Texture2D);
	void RemoveAllClickEvents();

	//±âº» ½½·Ô À§Á¬
	UFUNCTION()
	void SetBaseSlots();
	//À¯´Ö »ý¼º °Ç¹°µéÀÇ ½½·Ô À§Á¬
	UFUNCTION()
	void SetBuildSlots();
	UFUNCTION()
	void SetUpgradeBuildSlots();
	UFUNCTION()
	void SetSynBioLabSlots();
	//°Ç¹° Áþ±â »óÅÂÀÇ ½½·Ô À§Á¬
	UFUNCTION()
	void SetBuildingSlots();
	//¹è·° ½½·Ô À§Á¬
	UFUNCTION()
	void SetBarracksSlots();
	UFUNCTION()
	void SpawnRifleMan();
	UFUNCTION()
	void SpawnSwordMan();
	//»ý¸í¿¬±¸¼Ò ½½·Ô À§Á¬
	UFUNCTION()
	void SpawnMutant();
	//ÀÚ¿ø»ý»ê½Ã¼³ ½½·Ô À§Á¬
	UFUNCTION()
	void SetResourceFacilitySlots();
	UFUNCTION()
	void ResearchResourceProduction();
	//ºó À§Á¬
	UFUNCTION()
	void SetEmptySlots();

	//ÀÚ¿ø ºÎÁ· ¸Þ¼¼Áö Ç¥½Ã
	void NotEnoughMessage();


	void SetCommandWidgetState(FObjectInfo ObjectInfo);


	void ClearSlotsImage();
private:
	UTexture2D* Texture_BuildIcon;
	UTexture2D* Texture_TechIcon;
	UTexture2D* Texture_Empty;
	UTexture2D* Texture_StopBuilding;
	UMaterial* Texture_RifleMan;
	UMaterial* Texture_Barracks;

	class UCommanderBaseWidget* CommanderBaseWidget;
	class UTacticalStrikeGameInstance* GameInstance;
	
	//À¯´Ö »ý¼º °Ç¹° À§Á¬
	UFUNCTION()
	void Button_Barracks_OnClicked();
	UFUNCTION()
	void Button_SynBioLab_OnClicked();
	UFUNCTION()
	void Button_ResourceFacility_OnClicked();
	UFUNCTION()
	void Button_EnergyRepeater_OnClicked();

	UFUNCTION()
	void Button_StopBuilding_OnClicked();

	FTimerHandle MessageTimerHandle;
	uint8 MessageTextCountTime;
	void MessageTextHandle();

	bool CheckNull();

	uint8 DefaultObjectNumber;
};
