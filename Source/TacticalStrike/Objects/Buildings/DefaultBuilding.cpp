// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultBuilding.h"
#include "Kismet/GameplayStatics.h"
//#include "TacticalStrikeGameInstance.h"
#include "Components/WidgetComponent.h"
#include "Components/BuildingClickableComponent.h"
#include "Widgets/ObjectHealthWidget.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameMode/TacticalStrikeGameStateBase.h"

// Sets default values
ADefaultBuilding::ADefaultBuilding()
{
	PrimaryActorTick.bCanEverTick = false;
	ClickableComponent = CreateDefaultSubobject<UBuildingClickableComponent>(TEXT("DefaultBuilding_ClickableComponent"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DefaultBuilding_HpBarWidget"));
	NiagaraComponent_ObjectSelected = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_DefaultBuilding_ObjectSelected"));

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_DefaultBuilding"));

	//BuildEnableMat = CreateDefaultSubobject<UMaterialInterface>(TEXT("Building_Material_Enable"));
	//BuildDisableMat = CreateDefaultSubobject<UMaterialInterface>(TEXT("Building_Material_Disable"));

	DefaultBuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_DefaultBuilding"));
	DefaultBuildingMat = CreateDefaultSubobject<UMaterialInterface>(TEXT("Material_DefaultBuilding"));

	DefaultBuildingMesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FClassFinder<UObjectHealthWidget> HealthUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/BP_ObjectHealthWidget.BP_ObjectHealthWidget_C'"));
	if (HealthUI.Succeeded())
	{
		HPBarWidget->SetWidgetClass(HealthUI.Class);
		HPBarWidget->SetDrawSize(FVector2D(200.0f, 30.0f));
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Selected(TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/Niagara/Niagara_ObjectSelected.Niagara_ObjectSelected'"));
	if (Selected.Succeeded())
	{
		NiagaraSystem_ObjectSelected = Selected.Object;
		NiagaraComponent_ObjectSelected->SetAsset(NiagaraSystem_ObjectSelected);
		NiagaraComponent_ObjectSelected->bAutoActivate = true;
	}
	

	RootComponent = RootScene;
	DefaultBuildingMesh->SetupAttachment(RootScene);
	HPBarWidget->SetupAttachment(RootScene);
	NiagaraComponent_ObjectSelected->SetupAttachment(RootScene);
	//HPBarWidget->SetRelativeLocation(GetActorLocation());
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	//HPBarWidget->SetVisibility(false);

	NiagaraComponent_ObjectSelected->bAutoActivate = true;

	CurrentBuildTime = 0;
	//ObjectOwner = EObjectOwner::None;
	ObjectState = EObjectState::DeActivated;
}

void ADefaultBuilding::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance != nullptr)
	{
		BuildingDataInfo = GameInstance->GetBuildingTable(BuildingType);
		GridSizeX = BuildingDataInfo->GridSizeX;
		GridSizeY = BuildingDataInfo->GridSizeY;
		EnergyRange = BuildingDataInfo->EnergyRange;
		Armor = BuildingDataInfo->Armor;
		DefaultHP = BuildingDataInfo->MaxHP;
		CurrentHP = DefaultHP;
		BuildTime = BuildingDataInfo->BuildTime;

		ObjectInfo.BuildTime = BuildingDataInfo->BuildTime;
		ObjectInfo.CurrentBuildTime = 0;
		ObjectInfo.CurrentHP = CurrentHP;
		ObjectInfo.ObjectState = EObjectState::DeActivated;
		ObjectState = EObjectState::DeActivated;
		ObjectInfo.ObjectType = BuildingType;
		ObjectInfo.ObjectActor = this;
	}

	if (GameInstance != nullptr)
	{
		BuildEnableMat = GameInstance->BuildEnableMat;
		BuildDisableMat = GameInstance->BuildDisableMat;
	}

	SetBuildingScale();
}

// Called when the game starts or when spawned
void ADefaultBuilding::BeginPlay()
{
	Super::BeginPlay();

	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	TacticalStrikeGameStateBase = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	if (TacticalStrikeGameStateBase != nullptr)
		TacticalStrikeGameStateBase->PlayerTurnStartDelegate.AddDynamic(this, &ADefaultBuilding::UpdateTurn);

	NiagaraComponent_ObjectSelected->RegisterComponent();
	NiagaraComponent_ObjectSelected->Activate(true);

	this->Tags.Add("Building");
	DefaultBuildingMesh->SetCollisionProfileName(TEXT("Building"));

	Set_NiagaraComponent_ObjectSelected_Scale();
	Set_NiagaraComponent_ObjectSelected_Visibility(false);

	auto BuildingWidget = Cast<UObjectHealthWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != BuildingWidget)
	{
		BuildingWidget->BindBuildingWidget(this);
	}
}

float ADefaultBuilding::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHP = FMath::Clamp(int32(CurrentHP - (FinalDamage - Armor)), 0, DefaultHP);
	ObjectInfo.CurrentHP = CurrentHP;
	//UE_LOG(LogTemp, Log, TEXT("%d"), CurrentHP);
	OnBuildingHPChanged.Broadcast(this);
	//OnBuildingHPChanged.Broadcast(this);
	return FinalDamage;
}

float ADefaultBuilding::GetHealthRatio()
{
	//Super::GetHealthRatio();

	return (DefaultHP < KINDA_SMALL_NUMBER) ? 0.0f : (float(CurrentHP) / float(DefaultHP));
}

void ADefaultBuilding::SetEnableMat()
{
	DefaultBuildingMesh->SetMaterial(0, BuildEnableMat);
}

void ADefaultBuilding::SetDisableMat()
{
	DefaultBuildingMesh->SetMaterial(0, BuildDisableMat);
}

void ADefaultBuilding::SetBasicMat()
{
	DefaultBuildingMesh->SetMaterial(0, DefaultBuildingMat);
	//DefaultBuildingMesh->SetCollisionProfileName(TEXT("Buildings"));
}

void ADefaultBuilding::SetBuildingCustomDepth(bool Result)
{
	if (Result)
		DefaultBuildingMesh->SetRenderCustomDepth(true);
	else
		DefaultBuildingMesh->SetRenderCustomDepth(false);
}

void ADefaultBuilding::SetBuildingScale()
{
	FVector OriginalSize = DefaultBuildingMesh->Bounds.BoxExtent * 2.0f;
	if (OriginalSize.IsNearlyZero())
		return;
	float DefaultScaleX = (float(GridSizeX) * 100.0f) / OriginalSize.X;
	float DefaultScaleY = (float(GridSizeY) * 100.0f) / OriginalSize.Y;
	float AspectRatioZ = OriginalSize.Z / ((OriginalSize.X + OriginalSize.Y) * 0.5f);
	float DefaultScaleZ = ((DefaultScaleX + DefaultScaleY) * 0.5f) * AspectRatioZ;

	SetActorScale3D(FVector(DefaultScaleX * 0.8f, DefaultScaleY * 0.8f, DefaultScaleZ * 0.8f));
	//DefaultBuildingMesh->SetRelativeScale3D(FVector(DefaultScaleX * 0.8f, DefaultScaleY * 0.8f, DefaultScaleZ * 0.8f));
}

void ADefaultBuilding::BuildBuilding()
{

}

void ADefaultBuilding::UpdateTurn()
{
	ClickableComponent->UpdateBuildingState();
	Set_NiagaraComponent_ObjectSelected_Visibility(false);
	if (CurrentBuildTime < -100)
		return;

	CurrentBuildTime++;
	ObjectInfo.CurrentBuildTime = CurrentBuildTime;
		if (CurrentBuildTime >= BuildTime)
	{
		ActivateBuilding();
		CurrentBuildTime = -200;
	}
}

void ADefaultBuilding::ActivateBuilding()
{
	SetBasicMat();
	ObjectInfo.ObjectState = EObjectState::Activated;
	ObjectState = EObjectState::Activated;
	if (GridActor != nullptr)
	{
		FIntPoint BuildingGrid = GridActor->GetGridTile(GetActorLocation());
		if (GridActor->TileCheck(BuildingGrid.X, BuildingGrid.Y))
		{
			GridActor->SetTile_Building(BuildingGrid, this, true);
			//UE_LOG(LogTemp, Log, TEXT("Code: %d"), BuildingType);
			//GridActor->UpdateTurn();
		}
	}

}

void ADefaultBuilding::SetBuildingCollision()
{
	if (ObjectInfo.ObjectOwner == EObjectOwner::Blue)
		DefaultBuildingMesh->SetCollisionProfileName(TEXT("BlueTeamBuilding"));
	else if (ObjectInfo.ObjectOwner == EObjectOwner::Red)
		DefaultBuildingMesh->SetCollisionProfileName(TEXT("RedTeamBuilding"));
}

void ADefaultBuilding::Set_NiagaraComponent_ObjectSelected_Scale()
{
	float NiagaraScale = 0.0f;

	if (GridSizeX > GridSizeY)
		NiagaraScale = float(GridSizeX) * 6.0f;
	else if (GridSizeX < GridSizeY)
		NiagaraScale = float(GridSizeY) * 6.0f;
	else
		NiagaraScale = float(GridSizeX) * 6.0f;

	NiagaraComponent_ObjectSelected->SetVariableFloat(FName("MeshUniformScale"), NiagaraScale);
	NiagaraComponent_ObjectSelected->Activate(true);
}

void ADefaultBuilding::Set_NiagaraComponent_ObjectSelected_Visibility(bool Visibility)
{
	if (Visibility)
	{
		//NiagaraComponent_ObjectSelected->Deactivate();
		//NiagaraComponent_ObjectSelected->Activate(true);
		NiagaraComponent_ObjectSelected->SetVisibility(true);
	}
	else
	{
		NiagaraComponent_ObjectSelected->SetVisibility(false);
		//NiagaraComponent_ObjectSelected->Deactivate();
	}
}