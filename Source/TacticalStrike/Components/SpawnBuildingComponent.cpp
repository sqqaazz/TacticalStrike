// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBuildingComponent.h"
#include "Controllers/CommanderController.h"
#include "Objects/GridActor.h"
#include "DataTables/BuildingDataTables.h"
#include "Kismet/GameplayStatics.h"

#include "Objects/Buildings/DefaultBuilding.h"
#include "Objects/Buildings/Building_Barracks.h"
#include "Objects/Buildings/Building_SynBioLab.h"
#include "Objects/Buildings/Building_ResourceFacility.h"
#include "Objects/Buildings/Building_EnergyRepeater.h"

USpawnBuildingComponent::USpawnBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentBuildingCode = ESpawnBuilding::None;
	static ConstructorHelpers::FClassFinder<ABuilding_Barracks> Spawning_Barracks(TEXT("Class'/Script/TacticalStrike.Building_Barracks'"));
	if (Spawning_Barracks.Succeeded())
		Building_Barracks = Spawning_Barracks.Class;
	static ConstructorHelpers::FClassFinder<ABuilding_SynBioLab> Spawning_SynBioLab(TEXT("Class'/Script/TacticalStrike.Building_SynBioLab'"));
	if (Spawning_SynBioLab.Succeeded())
		Building_SynBioLab = Spawning_SynBioLab.Class;
	static ConstructorHelpers::FClassFinder<ABuilding_ResourceFacility> Spawning_ResourceFacility(TEXT("Class'/Script/TacticalStrike.Building_ResourceFacility'"));
	if (Spawning_ResourceFacility.Succeeded())
		Building_ResourceFacility = Spawning_ResourceFacility.Class;
	static ConstructorHelpers::FClassFinder<ABuilding_EnergyRepeater> Spawning_EnergyRepeater(TEXT("/Script/CoreUObject.Class'/Script/TacticalStrike.Building_EnergyRepeater'"));
	if (Spawning_EnergyRepeater.Succeeded())
		Building_EnergyRepeater = Spawning_EnergyRepeater.Class;

	CommanderController = Cast<ACommanderController>(GetOwner());
	//if (CommanderController != nullptr)

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	TickIsActived = false;
	DefaultBuildingLocation = FVector(-10000.0f, -10000.0f, -10000.0f);

	IsEnableBuilding = false;
}


// Called when the game starts
void USpawnBuildingComponent::BeginPlay()
{
	Super::BeginPlay();	
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
}


// Called every frame
void USpawnBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TickIsActived)
	{
		if (DefaultBuilding == nullptr)
			return;

		CommanderController->DeprojectMousePositionToWorld(SpawnLocation, SpawnDirection);

		CheckTraceResult_Grid(SpawnLocation, SpawnDirection);
	}

	//FHitResult GridHitResult;
	//GetHitResultUnderCursor(ECC_Visibility, false, GridHitResult);
	//GridActor->GetGridTile(GridHitResult);
}

void USpawnBuildingComponent::CheckTraceResult(FVector MouseLocation, FVector MouseDirection)
{
	//FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);


	GetWorld()->LineTraceSingleByChannel(
		Hit,
		MouseLocation,
		MouseDirection * 10000.0f + MouseLocation,
		ECollisionChannel::ECC_GameTraceChannel8);
	//UE_LOG(LogTemp, Log, TEXT("%f, %f"), MouseLocation.X, MouseLocation.Y);
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()) && !Hit.GetActor()->ActorHasTag("Building"))
	{
		//DrawDebugLine(GetWorld(), MouseLocation, MouseDirection * 10000.0f + MouseLocation, FColor::Green, false, 5.0f);
		//UE_LOG(LogTemp, Log, TEXT("x: %f, y: %f, z: %f"), Hit.Location.X, Hit.Location.Y, Hit.Location.Z);
		AdjustBuildingLocation = AdjustLocation(Hit);
		DefaultBuilding->SetActorLocation(AdjustBuildingLocation);
		DefaultBuilding->SetEnableMat();
	}
	else if (Hit.bBlockingHit && IsValid(Hit.GetActor()) && Hit.GetActor()->ActorHasTag("Building"))
	{
		AdjustBuildingLocation = AdjustLocation(Hit);
		DefaultBuilding->SetActorLocation(AdjustBuildingLocation);
		DefaultBuilding->SetDisableMat();
	}
	else
	{
		//DrawDebugLine(GetWorld(), MouseLocation, MouseDirection * 10000.0f + MouseLocation, FColor::Red, false, 5.0f);
	}
}

void USpawnBuildingComponent::CheckTraceResult_Grid(FVector MouseLocation, FVector MouseDirection)
{
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		MouseLocation,
		MouseDirection * 10000.0f + MouseLocation,
		ECollisionChannel::ECC_GameTraceChannel8);
	int32 TileRow = int32(FMath::Floor(Hit.Location.X / 100));
	int32 TileColumn = int32(FMath::Floor(Hit.Location.Y / 100));

	if (CurTileRow != TileRow || CurTileColumn != TileColumn)
	{
		CurTileRow = TileRow;
		CurTileColumn = TileColumn;
		float TileSize = GridActor->TileSize;
		if (GridActor->TileCheck(TileRow, TileColumn))
		{
			//UE_LOG(LogTemp, Log, TEXT("Row: %d, Column: %d"), TileRow, TileColumn);
			//DefaultBuilding->BuildingType
			//GridActor->ClearSquareVertices();
			FIntPoint BuildingStartGrid = GridActor->GetStartGridTile(TileRow, TileColumn, BuildingGridSizeX, BuildingGridSizeY, DefaultBuilding->ObjectOwner)	;
			GridActor->DrawBuildingGrid(BuildingStartGrid, BuildingGridSizeX, BuildingGridSizeY);
			IsEnableBuilding = GridActor->CheckEnableBuilding(BuildingStartGrid, BuildingGridSizeX, BuildingGridSizeY);
			//DefaultBuilding->SetActorLocation(FVector((TileRow * TileSize) + (TileSize / 2), (TileColumn * TileSize) + (TileSize / 2), 10.0f));
			//DefaultBuilding->SetEnableMat();
		}
	}
}

FVector USpawnBuildingComponent::AdjustLocation(FHitResult HitResult)
{
	float HitLocationX;
	float HitLocationY;

	if (FMath::Fmod(Hit.Location.X, 200.0f) < 100.0f)
	{
		HitLocationX = Hit.Location.X - FMath::Fmod(Hit.Location.X, 200.0f);
	}
	else
	{
		HitLocationX = Hit.Location.X - FMath::Fmod(Hit.Location.X, 200.0f) + 200.0f;
	}
	if (FMath::Fmod(Hit.Location.Y, 200.0f) < 100.0f)
	{
		HitLocationY = Hit.Location.Y - FMath::Fmod(Hit.Location.Y, 200.0f);
	}
	else
	{
		HitLocationY = Hit.Location.Y - FMath::Fmod(Hit.Location.Y, 200.0f) + 200.0f;
	}

	return FVector(HitLocationX, HitLocationY, HitResult.Location.Z);
}

void USpawnBuildingComponent::CheckEnableBuilding()
{
}

void USpawnBuildingComponent::SpawnBuildings_Grid()
{
	//UStaticMeshComponent* MeshComponent = DefaultBuilding->FindComponentByClass<UStaticMeshComponent>();
	//if (MeshComponent != nullptr)
	//	MeshComponent->SetCollisionProfileName(TEXT("Buildings"));

	int32 TileRow = int32(FMath::Floor(Hit.Location.X / 100));
	int32 TileColumn = int32(FMath::Floor(Hit.Location.Y / 100));
	//UE_LOG(LogTemp, Log, TEXT("%d, %d"), TileRow, TileColumn);
	float TileSize = GridActor->TileSize;

	FVector BuildingLocation = FVector((TileRow * TileSize) + (TileSize / 2), (TileColumn * TileSize) + (TileSize / 2), 15.0f);

	SpawnBuildingCode(CurrentBuildingCode, EObjectOwner::Blue, BuildingLocation);
	GridActor->SetTile_Building(FIntPoint(TileRow, TileColumn), DefaultBuilding, false);
	DefaultBuilding->SetEnableMat();
	//DefaultBuilding->SetActorLocation(FVector((TileRow * TileSize) + (TileSize / 2), (TileColumn * TileSize) + (TileSize / 2), 15.0f));

	GridActor->ClearPreviousGrid();
}

//void USpawnBuildingComponent::SpawnBuildings()
//{
//	if (!IsValid(Hit.GetActor()))
//		return;
//	else if (Hit.GetActor()->ActorHasTag("Building"))
//	{
//		return;
//	}
//	//DefaultBuilding->Destroy();
//	//SpawnBuildingCode(CurrentBuildingCode, AdjustBuildingLocation);
//	//DefaultBuilding->SetBasicMat();
//	UStaticMeshComponent* MeshComponent = DefaultBuilding->FindComponentByClass<UStaticMeshComponent>();
//	if (MeshComponent != nullptr)
//	{
//		MeshComponent->SetCollisionProfileName(TEXT("Buildings"));
//	}
//	if (Hit.GetActor()->ActorHasTag("BlueTeamMap"))
//		DefaultBuilding->Tags.Add("BlueTeamBuilding");
//	else if (Hit.GetActor()->ActorHasTag("RedTeamMap"))
//		DefaultBuilding->Tags.Add("RedTeamBuilding");
//}

void USpawnBuildingComponent::IsBuilding(ESpawnBuilding BuildingCode)
{
	CurrentBuildingCode = BuildingCode;
	if (GameInstance != nullptr)
	{
		BuildingDataInfo = GameInstance->GetBuildingTable(static_cast<int32>(CurrentBuildingCode));
		BuildingGridSizeX = BuildingDataInfo->GridSizeX;
		BuildingGridSizeY = BuildingDataInfo->GridSizeY;
	}

	SpawnBuildingCode(BuildingCode, EObjectOwner::Blue, DefaultBuildingLocation);
	TickIsActived = true;

}

void USpawnBuildingComponent::IsNotBuilding()
{
	//DefaultBuilding->Destroy();
	TickIsActived = false;
}

void USpawnBuildingComponent::IsEnterWidget()
{
	if (DefaultBuilding != nullptr)
	{
		DefaultBuilding_Temp = DefaultBuilding;
		DefaultBuilding->Destroy();
	}
}

void USpawnBuildingComponent::IsNotEnterWidget()
{
	if (DefaultBuilding != nullptr && CommanderController->Building)
		DefaultBuilding = GetWorld()->SpawnActor<ABuilding_Barracks>(Spawn_DefaultBuilding, FVector(6000.0f, 6000.0f, 1000.0f), FRotator(0.0f, 0.0f, 0.0f));

}

void USpawnBuildingComponent::SpawnBuildingCode(ESpawnBuilding BuildingCode, EObjectOwner ObjectOwner, FVector BuildingLocation)
{
	switch (BuildingCode)
	{
	case ESpawnBuilding::Barracks:
		Spawn_DefaultBuilding = Building_Barracks;
		DefaultBuilding = GetWorld()->SpawnActor<ABuilding_Barracks>(Spawn_DefaultBuilding, BuildingLocation, FRotator(0.0f, 0.0f, 0.0f));
		DefaultBuilding->ObjectOwner = ObjectOwner;
		DefaultBuilding->ObjectInfo.ObjectOwner = ObjectOwner;
		break;
	case ESpawnBuilding::SynBioLab:
		Spawn_DefaultBuilding = Building_SynBioLab;
		DefaultBuilding = GetWorld()->SpawnActor<ABuilding_SynBioLab>(Spawn_DefaultBuilding, BuildingLocation, FRotator(0.0f, 0.0f, 0.0f));
		DefaultBuilding->ObjectOwner = ObjectOwner;
		DefaultBuilding->ObjectInfo.ObjectOwner = ObjectOwner;
		break;
	case ESpawnBuilding::ResourceFacility:
		Spawn_DefaultBuilding = Building_ResourceFacility;
		DefaultBuilding = GetWorld()->SpawnActor<ABuilding_ResourceFacility>(Spawn_DefaultBuilding, BuildingLocation, FRotator(0.0f, 0.0f, 0.0f));
		DefaultBuilding->ObjectOwner = ObjectOwner;
		DefaultBuilding->ObjectInfo.ObjectOwner = ObjectOwner;
		break;
	case ESpawnBuilding::EnergyRepeater:
		Spawn_DefaultBuilding = Building_EnergyRepeater;
		DefaultBuilding = GetWorld()->SpawnActor<ABuilding_EnergyRepeater>(Spawn_DefaultBuilding, BuildingLocation, FRotator(0.0f, 0.0f, 0.0f));
		DefaultBuilding->ObjectOwner = ObjectOwner;
		DefaultBuilding->ObjectInfo.ObjectOwner = ObjectOwner;
		break;
	default:
		break;
	}
}
