// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderController.h"
#include "GameMode/TacticalStrikeGameStateBase.h"
#include "DrawDebugHelpers.h"
#include "Components/BuildingClickableComponent.h"
#include "Components/UnitClickableComponent.h"
#include "Components/SpawnBuildingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/CommanderBaseWidget.h"
#include "GameMode/TacticalStrikeGameStateBase.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Widgets/ResearchWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Objects/GridActor.h"
//#include "Characters/DefaultSpawningActor.h"

ACommanderController::ACommanderController()
{
	static ConstructorHelpers::FClassFinder<UCommanderBaseWidget> CommanderWidget(TEXT("WidgetBlueprint'/Game/Blueprints/Widgets/BP_CommanderUI.BP_CommanderUI_C'"));
	if (CommanderWidget.Succeeded())
	{
		BaseWidgetClass = CommanderWidget.Class;
	}

	//static ConstructorHelpers::FClassFinder<ABuilding_Barracks> Spawning_Barracks(TEXT("Class'/Script/TacticalStrike.Building_Barracks'"));
	//if (Spawning_Barracks.Succeeded())
	//{
	//	Spawn_Barracks = Spawning_Barracks.Class;
	//}

	SpawnBuildingComponent = CreateDefaultSubobject<USpawnBuildingComponent>(TEXT("Player_SpawnBuildingComponent"));

	//마우스 커서 보이게
	SetShowMouseCursor(true);
	//클릭 이벤트 활성화
	bEnableClickEvents = true;
	//bEnableMouseOverEvents = true;

	Mineral = 10000;
	Gas = 0;
	ChangeMineral = 0;
	ChangeGas = 0;

	Building = false;
	EnterWidgetState = false;

	//FInputModeGameOnly GameOnly;
	//this->SetInputMode(GameOnly);
}

void ACommanderController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("MouseLeftClicked", IE_Pressed, this, &ACommanderController::OnClickedEvent);
}

void ACommanderController::BeginPlay()
{
	Super::BeginPlay();

	//FInputModeUIOnly GameOnly;
	//this->SetInputMode(GameOnly);

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	FIntPoint Screen_FHD = (1920, 1080);
	GameUserSettings->SetScreenResolution(Screen_FHD);
	GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);

	GameUserSettings->ApplySettings(false);

	//위젯 띄우기
	BaseWidget = CreateWidget<UCommanderBaseWidget>(this, BaseWidgetClass);
	BaseWidget->AddToViewport();

	GetWorldCommanderTimer = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	if (GetWorldCommanderTimer != nullptr)
	{
		GetWorldCommanderTimer->WorldCommanderTimer.AddDynamic(this, &ACommanderController::UpdateWorldTimer);
	}
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void ACommanderController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FHitResult GridHitResult;
	//GetHitResultUnderCursor(ECC_Visibility, false, GridHitResult);
	//GridActor->GetGridTile(GridHitResult);

	//FHitResult MouseLocationVector;
	///GetHitResultUnderCursor(ECC_Visibility, false, MouseLocationVector);
	//UE_LOG(LogTemp, Log, TEXT("X: %f, Y: %f"), MouseLocationVector.Location.X, MouseLocationVector.Location.Y);

	//SetResource(ChangeMineral, ChangeGas, DeltaTime);
	//if (SelectedBuilding != nullptr)
	//{
	//	//진행상황 표기
	//	if (BuildingClickableComponent->UnitDataArray.Num() != 0 || BuildingClickableComponent->ResearchPercent != 0.0f)
	//	{
	//		if (SelectedBuilding->BuildingType < 150)
	//		{
	//			//UE_LOG(LogTemp, Log, TEXT("Product.."));
	//			BaseWidget->ObjectInfoWidget->BuildingInfoWidget->BuildWaitingWidget->BuildPercent = BuildingClickableComponent->BuildPercent;
	//			BaseWidget->ObjectInfoWidget->BuildingInfoWidget->BuildWaitingWidget->SetWaitingSlots(BuildingClickableComponent->UnitDataArray);
	//			//if (BuildingClickableComponent->UnitDataArray.Num() == 0)
	//			//	BaseWidget->ObjectInfoWidget->BuildingInfoWidget->SetDefaultInfo();
	//		}
	//		else
	//		{
	//			BaseWidget->ObjectInfoWidget->BuildingInfoWidget->ResearchWidget->ResearchPercent = BuildingClickableComponent->ResearchPercent;
	//			BaseWidget->ObjectInfoWidget->BuildingInfoWidget->SetResearchInfo();
	//			//if (BuildingClickableComponent->ResearchPercent == KINDA_SMALL_NUMBER)
	//			//	BaseWidget->ObjectInfoWidget->BuildingInfoWidget->SetResearchInfo();
	//			//else
	//			//	BaseWidget->ObjectInfoWidget->BuildingInfoWidget->SetResearchInfo();
	//			//UE_LOG(LogTemp, Log, TEXT("%f"), BuildingClickableComponent->ResearchPercent);
	//		}
	//	}
	//	else
	//		BaseWidget->ObjectInfoWidget->BuildingInfoWidget->SetDefaultInfo();
	//}
}

void ACommanderController::UpdateWorldTimer()
{
	ChangeMineral += 30;
}

void ACommanderController::UpdateTurn()
{
	//SetObjectHighlight(ClickedDefaultObject, false);
}

//자원 관리 함수
void ACommanderController::SetResource(uint32 MineralChange, uint32 GasChange, float DeltaTime)
{
	if (FMath::RoundToInt(ChangeMineral) != 0)
	{
		float MineralChangeWeight = DeltaTime * 50 * FMath::Clamp(FMath::Abs(ChangeMineral) / 20, 1.0f, 500.0f);
		if (ChangeMineral > 0)
		{
			Mineral = FMath::Clamp(Mineral + MineralChangeWeight, Mineral, Mineral + ChangeMineral);
			ChangeMineral -= MineralChangeWeight;
		}
		else if (ChangeMineral < 0)
		{
			Mineral = FMath::Clamp(Mineral - MineralChangeWeight, Mineral + ChangeMineral, Mineral);
			ChangeMineral += MineralChangeWeight;
		}
	}
}

void ACommanderController::OnClickedEvent()
{

	//FHitResult GridHitResult;
	//GetHitResultUnderCursor(ECC_Visibility, false, GridHitResult);
	//GridActor->GetGridTile(GridHitResult);

	if (!Building)
	{
		GetHitResultUnderCursor(ECC_Visibility, false, MouseHitResult);
		//UE_LOG(LogTemp, Log, TEXT("gvvvvvvvvvccddd"));
		if (MouseHitResult.bBlockingHit && (MouseHitResult.GetActor()->ActorHasTag("Building") || MouseHitResult.GetActor()->ActorHasTag("Unit")))
		{
			SetObjectHighlight(MouseHitResult.GetActor(), true);
			ClickedDefaultObject = MouseHitResult.GetActor();
		}


		if (MouseHitResult.bBlockingHit && MouseHitResult.GetActor()->ActorHasTag("Building"))
		{
			//UE_LOG(LogTemp, Log, TEXT("Buildingdddddddddddd"));
			//uint8 Code = 0;
			//EObjectState State = EObjectState::None;
			BuildingClickableComponent = Cast<UBuildingClickableComponent>(MouseHitResult.GetActor()->GetComponentByClass(UBuildingClickableComponent::StaticClass()));
			//ADefaultBuilding* ClickedBuilding = Cast<ADefaultBuilding>(MouseHitResult.GetActor());
			SelectedBuilding = Cast<ADefaultBuilding>(MouseHitResult.GetActor());
			if (SelectedBuilding != nullptr)
			{
				FObjectInfo ObjectInfo = SelectedBuilding->ObjectInfo;
				//Code = SelectedBuilding->BuildingType;
				//State = SelectedBuilding->ObjectState;
				BaseWidget->SetWidgetState(ObjectInfo);
			}
		}
		else if (MouseHitResult.bBlockingHit && MouseHitResult.GetActor()->ActorHasTag("Unit"))
		{
			
		}
		else
		{
			FObjectInfo ObjectInfo(0, 0, EObjectState::None, 0, 0, EObjectOwner::None, 0, nullptr);
			BaseWidget->SetWidgetState(ObjectInfo);
			//ClickedDefaultObject->Set_NiagaraComponent_ObjectSelected_Visibility(false);
			SetObjectHighlight(ClickedDefaultObject, false);
	
			ClickedDefaultObject = nullptr;
			//DisableAllHighlight();
		}

	}
	else
	{
		if (!SpawnBuildingComponent->IsEnableBuilding)
			return;
		SpawnBuildingComponent->SpawnBuildings_Grid();
		IsNotBuilding();
		FObjectInfo ObjectInfo(0, 0, EObjectState::None, 0, 0, EObjectOwner::None, 0, nullptr);
		BaseWidget->SetWidgetState(ObjectInfo);
	}
}

void ACommanderController::BuildingUnits(ESpawnBuilding BuildingType, ESpawnUnit UnitType)
{
	if (BuildingClickableComponent != nullptr)
	{	
		ADefaultBuilding* SpawnBuilding =  Cast<ADefaultBuilding>(BuildingClickableComponent->GetOwner());
		if (SpawnBuilding != nullptr)
		{
			SpawnBuilding->ObjectInfo.ObjectState = EObjectState::BuildWaited;
			SpawnBuilding->ObjectState = EObjectState::BuildWaited;
			FObjectInfo BuildingObjectInfo = SpawnBuilding->ObjectInfo;

			FUnitTableRow* UnitDataInfo = GameInstance->GetUnitTable(static_cast<int32>(UnitType));
			if (UnitDataInfo != nullptr)
			{
				FObjectInfo UnitObjectInfo(static_cast<int32>(UnitType), UnitDataInfo->MaxHP, EObjectState::DeActivated, UnitDataInfo->BuildTime, 0, EObjectOwner::Blue, 0, nullptr);

				//UE_LOG(LogTemp, Log, TEXT("%d"), UnitObjectInfo.ObjectType);
				BuildingClickableComponent->UnitDataArray.Emplace(UnitObjectInfo);
				BaseWidget->ObjectBuildingInfo(BuildingObjectInfo);
			}
		}

		//if (BuildingClickableComponent->UnitDataArray.Num() == 0)
		//{
		//	BuildingClickableComponent->UnitDataArray.Emplace(GameInstance->GetUnitTable(static_cast<int32>(UnitType)));
		//	BaseWidget->ObjectBuildingInfo(BuildingObjectInfo, 0);
		//}
		//else if (BuildingClickableComponent->UnitDataArray.Num() < 5)
		//{
		//	BuildingClickableComponent->UnitDataArray.Emplace(GameInstance->GetUnitTable(static_cast<int32>(UnitType)));
		//	BaseWidget->ObjectBuildingInfo(BuildingObjectInfo, BuildingClickableComponent->UnitDataArray.Num());
		//}
	}
}

void ACommanderController::BuildingUpgrade(uint8 UpgradeType)
{

	if (BuildingClickableComponent != nullptr)
	{
		BuildingClickableComponent->GetResearchTime(UpgradeType);
	}
}

void ACommanderController::ResearchComplete(uint8 ResearchType, FString Team)
{
	//UE_LOG(LogTemp, Log, TEXT("Resource Research Complete!!"));
	if (Team == "Blue")
		ResourceProductionDelegate.Broadcast("Blue");
	else if (Team == "Red")
		ResourceProductionDelegate.Broadcast("Red");
	BaseWidget->ObjectInfoWidget->BuildingInfoWidget->SetDefaultInfo();
}

void ACommanderController::IsBuilding(ESpawnBuilding BuildingCode)
{
	Building = true;
	SpawnBuildingComponent->IsBuilding(BuildingCode);
}

void ACommanderController::IsNotBuilding()
{
	Building = false;
	SpawnBuildingComponent->IsNotBuilding();
}

void ACommanderController::IsEnterWidget()
{
	//EnterWidgetState = true;
	//SpawnBuildingComponent->IsEnterWidget();
	//FInputModeUIOnly InputMode;
	//this->SetInputMode(InputMode);
	//UE_LOG(LogTemp, Log, TEXT("Enter"));
}

void ACommanderController::IsNotEnterWidget()
{
	//EnterWidgetState = false;
	//SpawnBuildingComponent->IsNotEnterWidget();
//	FInputModeGameOnly InputMode;
	//this->SetInputMode(InputMode);
	//UE_LOG(LogTemp, Log, TEXT("NotEnter"));
}

void ACommanderController::SetDefaultObjectInfo()
{
	FObjectInfo ObjectInfo(0, 0, EObjectState::None, 0, 0, EObjectOwner::None, 0, nullptr);
	BaseWidget->SetWidgetState(ObjectInfo);
}

//void ACommanderController::SetUnitInfo(uint8 Type)
//{
//	BaseWidget->SetUnitInfo(Type);
//}

void ACommanderController::UpdateObjectInfo(FObjectInfo ObjectInfo)
{
	BaseWidget->UpdateObjectInfo(ObjectInfo);
}

void ACommanderController::SetObjectHighlight(AActor* ClickedActor, bool Visibility)
{
	ADefaultUnit* ClickedPreviousDefaultUnit = Cast<ADefaultUnit>(ClickedDefaultObject);
	if (ClickedPreviousDefaultUnit != nullptr)
	{
		ClickedPreviousDefaultUnit->Set_NiagaraComponent_ObjectSelected_Visibility(false);
	}
	ADefaultBuilding* ClickedPreviousDefaultBuilding = Cast<ADefaultBuilding>(ClickedDefaultObject);
	if (ClickedPreviousDefaultBuilding != nullptr)
	{
		ClickedPreviousDefaultBuilding->Set_NiagaraComponent_ObjectSelected_Visibility(false);
	}

	//ADefaultUnit* CurrentSelectedUnit = Cast<ADefaultUnit>(ClickedDefaultObject);
	//if (CurrentSelectedUnit != nullptr)
	//	CurrentSelectedUnit->Set_NiagaraComponent_ObjectSelected_Visibility(Visibility);
	//ADefaultBuilding* CurrentSelectedBuilding = Cast<ADefaultBuilding>(ClickedDefaultObject);
	//	CurrentSelectedBuilding->Set_NiagaraComponent_ObjectSelected_Visibility(Visibility);

	ADefaultUnit* ClickedDefaultUnit = Cast<ADefaultUnit>(ClickedActor);
	if (ClickedDefaultUnit != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("bbbbbbbbbbbhhhhhhhhhfffffffff"));
		ClickedDefaultUnit->Set_NiagaraComponent_ObjectSelected_Visibility(Visibility);
		return;
	}
	ADefaultBuilding* ClickedDefaultBuilding = Cast<ADefaultBuilding>(ClickedActor);
	if (ClickedDefaultBuilding != nullptr)
	{
		ClickedDefaultBuilding->Set_NiagaraComponent_ObjectSelected_Visibility(Visibility);
		//ClickedDefaultBuilding->SetBuildingCustomDepth(true);
	}
}

//void ACommanderController::DisableAllHighlight()
//{
//	TArray<AActor*> ActorsToFind;
//	if (UWorld* World = GetWorld())
//	{
//		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsToFind);
//		for (AActor* Actorlist : ActorsToFind)
//		{
//			ADefaultUnit* ClickedDefaultUnit = Cast<ADefaultUnit>(Actorlist);
//			if (ClickedDefaultUnit != nullptr)
//			{
//				ClickedDefaultUnit->SetUnitCustomDepth(false);
//				continue;
//			}
//			ADefaultBuilding* ClickedDefaultBuilding = Cast<ADefaultBuilding>(Actorlist);
//			if (ClickedDefaultBuilding != nullptr)
//				ClickedDefaultBuilding->SetBuildingCustomDepth(false);
//		}
//	}
//}

void ACommanderController::ViewGridTile()
{
	GridActor->ViewGridTile();
}