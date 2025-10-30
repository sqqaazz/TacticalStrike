// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandWidget.h"
#include "CommandSlotsWidget.h"
#include "CommanderBaseWidget.h"
#include "UnitTooltipWidget.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DataTables/UnitDataTables.h"
#include "Components/TextBlock.h"

//UCommandWidget::UCommandWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
//{
//
//}

void UCommandWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_0"))));
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_1"))));
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_2"))));
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_3"))));
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_4"))));
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_5"))));
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_6"))));
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_7"))));
	BuildingSlotsArray.Add(Cast<UCommandSlotsWidget>(GetWidgetFromName(TEXT("BP_CommandSlots_8"))));

	GetCommanderController = Cast<ACommanderController>(Cast<APlayerController>(GetOwningPlayerPawn()->GetController()));
	CommanderBaseWidget = Cast<UCommanderBaseWidget>(GetCommanderController->BaseWidget);
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	MessageTextCountTime = 2;
	DefaultObjectNumber = 0;
}

void UCommandWidget::SetCommandWidgetState(FObjectInfo ObjectInfo)
{
	if (ObjectInfo.ObjectState == EObjectState::DeActivated)
	{
		SetEmptySlots();
		return;
	}

	switch (static_cast<ESpawnBuilding>(ObjectInfo.ObjectType))
	{
	case ESpawnBuilding::None:
		SetBaseSlots();
		break;
	case ESpawnBuilding::Barracks:
		SetBarracksSlots();
		break;
	case ESpawnBuilding::SynBioLab:
		SetSynBioLabSlots();
		break;
	case ESpawnBuilding::ResourceFacility:
		SetResourceFacilitySlots();
		break;
	default:
		SetEmptySlots();
		break;
	}
}

void UCommandWidget::ClearSlotsImage()
{
	for (uint8 i = 0; i < BuildingSlotsArray.Num(); i++)
	{
		if (BuildingSlotsArray[i] != nullptr)
		{
			BuildingSlotsArray[i]->SetSlotImageMat(GameInstance->Texture_Transparency);
		}
	}
}

//±âº» ½½·Ô À§Á¬
void UCommandWidget::SetBaseSlots()
{
	ClearSlotsImage();
	RemoveAllClickEvents();

	BuildingSlotsArray[6]->SetSlotImageTexture2D(GameInstance->Texture_BuildIcon);
	BuildingSlotsArray[7]->SetSlotImageTexture2D(GameInstance->Texture_TechIcon);

	BuildingSlotsArray[6]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::SetBuildSlots);
	BuildingSlotsArray[7]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::SetUpgradeBuildSlots);
}

//À¯´Ö »ý¼º °Ç¹°µéÀÇ ½½·Ô À§Á¬
void UCommandWidget::SetBuildSlots()
{
	ClearSlotsImage();
	RemoveAllClickEvents();

	BuildingSlotsArray[0]->SetSlotImageMat(GameInstance->GetMaterial(ESpawnObject::Barracks));
	BuildingSlotsArray[3]->SetSlotImageMat(GameInstance->GetMaterial(ESpawnObject::SynBioLab));

	BuildingSlotsArray[0]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::Button_Barracks_OnClicked);
	BuildingSlotsArray[3]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::Button_SynBioLab_OnClicked);
	BuildingSlotsArray[0]->SetObjectType(101);
	BuildingSlotsArray[3]->SetObjectType(102);

}
//¾÷±×·¹ÀÌµå °Ç¹°µéÀÇ ½½·Ô À§Á¬
void UCommandWidget::SetUpgradeBuildSlots()
{
	ClearSlotsImage();
	RemoveAllClickEvents();

	BuildingSlotsArray[0]->SetSlotImageMat(GameInstance->GetMaterial(ESpawnObject::ResourceFacility));
	BuildingSlotsArray[3]->SetSlotImageMat(GameInstance->GetMaterial(ESpawnObject::EnergyRepeater));
	BuildingSlotsArray[0]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::Button_ResourceFacility_OnClicked);
	BuildingSlotsArray[3]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::Button_EnergyRepeater_OnClicked);
	BuildingSlotsArray[0]->SetObjectType(202);
	BuildingSlotsArray[3]->SetObjectType(121);
}

//°Ç¼³ Áß
void UCommandWidget::SetBuildingSlots()
{
	ClearSlotsImage();
	RemoveAllClickEvents();

	BuildingSlotsArray[8]->SetSlotImageTexture2D(GameInstance->Texture_StopBuilding);
	//SetBuildingSlotsTexture(BuildingSlots_8, GameInstance->Texture_StopBuilding);

	BuildingSlotsArray[8]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::Button_StopBuilding_OnClicked);

}
//Barracks À¯´Ö
void UCommandWidget::SetBarracksSlots()
{
	ClearSlotsImage();
	RemoveAllClickEvents();

	BuildingSlotsArray[0]->SetSlotImageMat(GameInstance->GetMaterial(ESpawnObject::RifleMan));
	BuildingSlotsArray[1]->SetSlotImageMat(GameInstance->GetMaterial(ESpawnObject::SwordMan));
	BuildingSlotsArray[0]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::SpawnRifleMan);
	BuildingSlotsArray[1]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::SpawnSwordMan);

	BuildingSlotsArray[0]->SetObjectType(1);
	BuildingSlotsArray[1]->SetObjectType(2);
}
//SynBioLabs À¯´Ö
void UCommandWidget::SetSynBioLabSlots()
{
	ClearSlotsImage();
	RemoveAllClickEvents();

	BuildingSlotsArray[0]->SetSlotImageMat(GameInstance->GetMaterial(ESpawnObject::Mutant));
	BuildingSlotsArray[0]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::SpawnMutant);

	BuildingSlotsArray[0]->SetObjectType(3);
}

//ResourceFacility 
void UCommandWidget::SetResourceFacilitySlots()
{
	ClearSlotsImage();
	RemoveAllClickEvents();

	BuildingSlotsArray[0]->SetSlotImageTexture2D(GameInstance->Texture_ResourceUpgrade);

	BuildingSlotsArray[0]->BuildingButton->OnClicked.AddDynamic(this, &UCommandWidget::ResearchResourceProduction);
}

void UCommandWidget::SetEmptySlots()
{
	ClearSlotsImage();
	RemoveAllClickEvents();
}


void UCommandWidget::SpawnRifleMan()
{
	if (GetCommanderController != nullptr && GameInstance != nullptr)
	{
		FUnitTableRow* UnitData = GameInstance->GetUnitTable(1);
		if (GetCommanderController->Mineral + GetCommanderController->ChangeMineral > UnitData->Cost)
		{
			GetCommanderController->ChangeMineral -= UnitData->Cost;
			GetCommanderController->BuildingUnits(ESpawnBuilding::Barracks, ESpawnUnit::RifleMan);
		}
		else
			NotEnoughMessage();
	}
}

void UCommandWidget::SpawnSwordMan()
{
	if (GetCommanderController != nullptr && GameInstance != nullptr)
	{
		FUnitTableRow* UnitData = GameInstance->GetUnitTable(2);
		if (GetCommanderController->Mineral + GetCommanderController->ChangeMineral > UnitData->Cost)
		{
			GetCommanderController->ChangeMineral -= UnitData->Cost;
			GetCommanderController->BuildingUnits(ESpawnBuilding::Barracks, ESpawnUnit::SwordMan);
		}
		else
			NotEnoughMessage();
	}
}

void UCommandWidget::SpawnMutant()
{
	if (GetCommanderController != nullptr && GameInstance != nullptr)
	{
		FUnitTableRow* UnitData = GameInstance->GetUnitTable(3);
		if (GetCommanderController->Mineral + GetCommanderController->ChangeMineral > UnitData->Cost)
		{
			GetCommanderController->ChangeMineral -= UnitData->Cost;
			GetCommanderController->BuildingUnits(ESpawnBuilding::SynBioLab, ESpawnUnit::Mutant);
		}
		else
			NotEnoughMessage();
	}
}


void UCommandWidget::ResearchResourceProduction()
{
	if (GetCommanderController != nullptr)
	{
		GetCommanderController->BuildingUpgrade(221);
	}
}

void UCommandWidget::Button_Barracks_OnClicked()
{
	//Button_Barracks->SetVisibility(ESlateVisibility::Collapsed);
	//GetCommanderController = Cast<ACommanderController>(Cast<APlayerController>(GetOwningPlayerPawn()->GetController()));
	if (GetCommanderController != nullptr)
		GetCommanderController->IsBuilding(ESpawnBuilding::Barracks);
		SetBuildingSlots();

}

void UCommandWidget::Button_SynBioLab_OnClicked()
{
	if (GetCommanderController != nullptr)
		GetCommanderController->IsBuilding(ESpawnBuilding::SynBioLab);
	SetBuildingSlots();
}

void UCommandWidget::Button_EnergyRepeater_OnClicked()
{
	if (GetCommanderController != nullptr)
		GetCommanderController->IsBuilding(ESpawnBuilding::EnergyRepeater);
	SetBuildingSlots();
}

void UCommandWidget::Button_ResourceFacility_OnClicked()
{
	if (GetCommanderController != nullptr)
		GetCommanderController->IsBuilding(ESpawnBuilding::ResourceFacility);
	SetBuildingSlots();
}

void UCommandWidget::Button_StopBuilding_OnClicked()
{
	//GetCommanderController = Cast<ACommanderController>(Cast<APlayerController>(GetOwningPlayerPawn()->GetController()));
	if (GetCommanderController != nullptr)
	{
		GetCommanderController->IsNotBuilding();
	}
	SetBaseSlots();
}

void UCommandWidget::SetBuildingSlotsMat(class UCommandSlotsWidget* TargetSlot, UMaterial* Texture2D)
{
	TargetSlot->BuildingIconTexture->SetBrushFromMaterial(Texture2D);
}

void UCommandWidget::SetBuildingSlotsTexture(class UCommandSlotsWidget* TargetSlot, UTexture2D* Texture2D)
{
	TargetSlot->BuildingIconTexture->SetBrushFromTexture(Texture2D);
}

void UCommandWidget::RemoveAllClickEvents()
{
	if (CheckNull() == false)
		return;
	for (uint8 i = 0; i < BuildingSlotsArray.Num(); i++)
	{
		if (BuildingSlotsArray[i] != nullptr)
		{
			BuildingSlotsArray[i]->BuildingButton->OnClicked.RemoveAll(this);
			BuildingSlotsArray[i]->SetObjectType(DefaultObjectNumber);
		}
	}
}

bool UCommandWidget::CheckNull()
{
	for (uint8 i = 0; i < BuildingSlotsArray.Num(); i++)
	{
		if (BuildingSlotsArray[i] == nullptr)
			return false;
	}
	return true;
}

void UCommandWidget::NotEnoughMessage()
{
	FString MessageText = FString::Printf(TEXT("Not enough minerals.."));
	GetWorld()->GetTimerManager().SetTimer(MessageTimerHandle, this, &UCommandWidget::MessageTextHandle, 1.0f, true);
	//MessageTimer.SetTimer(Timerhandle)
	CommanderBaseWidget->MessageText->SetText(FText::FromString(MessageText));
}

void UCommandWidget::MessageTextHandle()
{
	--MessageTextCountTime;
	if (MessageTextCountTime < 1)
	{
		MessageTextCountTime = 2;
		FString MessageText = FString::Printf(TEXT(""));
		CommanderBaseWidget->MessageText->SetText(FText::FromString(MessageText));
		GetWorld()->GetTimerManager().ClearTimer(MessageTimerHandle);
	}
}