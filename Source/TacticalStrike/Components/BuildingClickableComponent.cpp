// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingClickableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/CommanderMap.h"
#include "Controllers/CommanderController.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "DataTables/UpgradeDataTables.h"
#include "DataTables/UnitDataTables.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Characters/DefaultSpawningActor.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"

// Sets default values for this component's properties
UBuildingClickableComponent::UBuildingClickableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


	CurBuildTime = 0;
	CurResearchTime = 0;

	BuildPercent = 0;
	ResearchPercent = 0;

	DefaultResearchTime = 0;
	ResearchType = 0;
}


// Called when the game starts
void UBuildingClickableComponent::BeginPlay()
{
	Super::BeginPlay();
	CommanderController = Cast<ACommanderController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DefaultBuilding = Cast<ADefaultBuilding>(GetOwner());

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACommanderMap::StaticClass(), SpawnUnitArray);
	//if (SpawnUnitArray[0]->ActorHasTag("RedTeamMap"))
	//{
	//	SpawnRedCommanderMap = Cast<ACommanderMap>(SpawnUnitArray[0]);
	//	SpawnBlueCommanderMap = Cast<ACommanderMap>(SpawnUnitArray[1]);
	//}
	//else if (SpawnUnitArray[1]->ActorHasTag("RedTeamMap"))
	//{
	//	SpawnRedCommanderMap = Cast<ACommanderMap>(SpawnUnitArray[1]);
	//	SpawnBlueCommanderMap = Cast<ACommanderMap>(SpawnUnitArray[0]);
	//}
	MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (MeshComponent != nullptr)
		GetOwner()->OnClicked.AddDynamic(this, &UBuildingClickableComponent::ClickEvent);
	
	if (DefaultBuilding != nullptr)
		DefaultBuilding->OnBuildingHPChanged.AddUObject(this, &UBuildingClickableComponent::UpdateBuildingHP);

	DefaultSpawningActor = Cast<ADefaultSpawningActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ADefaultSpawningActor::StaticClass()));
}


// Called every frame
//void UBuildingClickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	if (DefaultBuilding != nullptr)
//	{
//		if (DefaultBuilding->BuildingType < 150)
//			SetUnitBuildingState(DeltaTime);
//		else if (DefaultBuilding->BuildingType >= 150 && DefaultResearchTime != 0)
//			SetResearchingState(DeltaTime);
//	}
//}

void UBuildingClickableComponent::SetUnitBuildingState(float DeltaTime)
{
	//if (UnitDataArray.Num() == 0)
	//	return;

	//CurBuildTime += DeltaTime;
	//BuildPercent = CurBuildTime / UnitDataArray[0]->BuildTime;

	//if (CurBuildTime > UnitDataArray[0]->BuildTime)
	//{
	//	if (GetOwner()->ActorHasTag("BlueTeamBuilding"))
	//		SpawnBlueCommanderMap->BuildingUnitSpawn("Blue", UnitDataArray[0]->UnitType);
	//	else if (GetOwner()->ActorHasTag("RedTeamBuildings"))
	//		SpawnRedCommanderMap->BuildingUnitSpawn("Red", UnitDataArray[0]->UnitType);
	//	UnitDataArray.RemoveAt(0);
	//	CurBuildTime = 0;
	//	BuildPercent = 0;
	//}
}

void UBuildingClickableComponent::SetResearchingState(float DeltaTime)
{
	//if (DefaultResearchTime != 0)
	//{
	//	CurResearchTime += DeltaTime;
	//	ResearchPercent = CurResearchTime / DefaultResearchTime;

	//	//연구 완료 시 정보 초기화
	//	if (CurResearchTime > DefaultResearchTime)
	//	{
	//		if (DefaultBuilding->ActorHasTag("RedTeamBuildings"))
	//		{
	//			if (CommanderController != nullptr)
	//				CommanderController->ResearchComplete(ResearchType, "Red");
	//		}
	//		else
	//		{
	//			if (CommanderController != nullptr)
	//				CommanderController->ResearchComplete(ResearchType, "Blue");
	//		}
	//		DefaultResearchTime = 0.0f;
	//		ResearchPercent = 0.0f;
	//		ResearchType = 0;
	//		CurResearchTime = 0.0f;
	//	}
	//}
}

void UBuildingClickableComponent::GetResearchTime(uint8 GetResearchType)
{
	if (GameInstance != nullptr)
	{
		UpgradeDataInfo = GameInstance->GetUpgradeTable(GetResearchType);
		ResearchType = GetResearchType;
		if (UpgradeDataInfo != nullptr)
			DefaultResearchTime = UpgradeDataInfo->BuildTime;
	}
}

void UBuildingClickableComponent::ClickEvent(AActor* TouchedActor, FKey ButtonPressed)
{
	auto BuildingInfo = Cast<ADefaultBuilding>(TouchedActor);
	if (CommanderController != nullptr && BuildingInfo != nullptr)
	{
		//CommanderController->ClickedDefaultObject = TouchedActor;
		//CommanderController->UpdateObjectInfo(BuildingInfo->BuildingType, BuildingInfo->CurrentHP);

		//CommanderController->SetObjectHighlight(TouchedActor, true);
	}
}

void UBuildingClickableComponent::UpdateBuildingHP(/*ADefaultBuilding* ClickedDefaultBuilding*/)
{
	//AActor* ClickedActor = Cast<AActor>(ClickedDefaultBuilding);
	if (DefaultBuilding != nullptr && CommanderController != nullptr && GetOwner() != nullptr &&
		CommanderController->ClickedDefaultObject == GetOwner())
	{
		//FObjectInfo ClickedObjectInfo(DefaultBuilding->BuildingType, DefaultBuilding->CurrentHP, DefaultBuilding->ObjectState, DefaultBuilding->BuildTime, DefaultBuilding->CurrentBuildTime, DefaultBuilding->ObjectInfo.ObjectOwner, DefaultBuilding->ObjectInfo.Actions,DefaultBuilding);
		FObjectInfo ClickedObjectInfo(DefaultBuilding->ObjectInfo);
		//ClickedObjectInfo.CurrentBuildTime = DefaultBuilding->CurrentBuildTime;


		CommanderController->UpdateObjectInfo(ClickedObjectInfo);
	}
}

void UBuildingClickableComponent::UpdateBuildingState()
{
	if (UnitDataArray.Num() > 0)
	{
		UnitDataArray[0].CurrentBuildTime++;
		//UE_LOG(LogTemp, Log, TEXT("Time: %d"), UnitDataArray[0].CurrentBuildTime);
		if (DefaultBuilding != nullptr && UnitDataArray[0].CurrentBuildTime >= UnitDataArray[0].BuildTime)
		{
				DefaultSpawningActor->SpawnUnit(UnitDataArray[0], DefaultBuilding);
				UnitDataArray.RemoveAt(0);

				if (UnitDataArray.Num() == 0)
				{
					DefaultBuilding->ObjectState = EObjectState::Activated;
					DefaultBuilding->ObjectInfo.ObjectState = EObjectState::Activated;
				}
			
		}
	}
}