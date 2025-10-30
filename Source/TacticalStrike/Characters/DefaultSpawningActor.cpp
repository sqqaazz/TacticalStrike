// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultSpawningActor.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/CommanderMap.h"
#include "Objects/GridActor.h"
#include "Controllers/CommanderController.h"
#include "AI/AIController/CommanderAI.h"
#include "Characters/CommanderUnit.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "CommanderUnit.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/Units/RifleMan/RifleMan.h"
#include "Characters/Units/SwordMan/SwordMan.h"
#include "Characters/Units/Mutant/Mutant.h"

#include "Objects/Buildings/Building_Crystal.h"
#include "Objects/Buildings/Building_Barracks.h"
#include "Objects/Buildings/Building_ResourceFacility.h"
#include "Objects/Buildings/Building_SynBioLab.h"
#include "Objects/Buildings/Building_EnergyRepeater.h"
#include "DrawDebugHelpers.h"

// Sets default values
ADefaultSpawningActor::ADefaultSpawningActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_DefaultSpawningActor"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SpawningActorMesh(TEXT("StaticMesh'/Game/3DModels/StaticMesh/Crystal/crystals/source/Crystals_SM.Crystals_SM'"));
	if (SpawningActorMesh.Succeeded())
		StaticMesh->SetStaticMesh(SpawningActorMesh.Object);

	//스폰할 오브젝트들의 클래스
	static ConstructorHelpers::FClassFinder<ABuilding_Crystal> Spawning_Crystal(TEXT("Class'/Script/TacticalStrike.Building_Crystal'"));
	if (Spawning_Crystal.Succeeded())
		Building_Crystal = Spawning_Crystal.Class;
	StaticMesh->SetRelativeScale3D(FVector(50.0f, 50.0f, 50.0f));

	//스폰할 유닛들의 클래스
	//static ConstructorHelpers::FClassFinder<ARifleMan> RifleMan_Spawn(TEXT("Blueprint'/Game/Blueprints/Count/BP_RifleMan_Count.BP_RifleMan_Count_C'"));
	//if (RifleMan_Spawn.Succeeded())
	//	SpawnRifleMan = RifleMan_Spawn.Class;
	//static ConstructorHelpers::FClassFinder<ASwordMan> SwordMan_Spawn(TEXT("Blueprint'/Game/Blueprints/Count/BP_SwordMan_Count.BP_SwordMan_Count_C'"));
	//if (SwordMan_Spawn.Succeeded())
	//	SpawnSwordMan = SwordMan_Spawn.Class;
	//static ConstructorHelpers::FClassFinder<AMutant> Mutant_Spawn(TEXT("Blueprint'/Game/Blueprints/Count/BP_Mutant_Count.BP_Mutant_Count_C'"));
	//if (Mutant_Spawn.Succeeded())
	//	SpawnMutant = Mutant_Spawn.Class;

	static ConstructorHelpers::FClassFinder<ARifleMan> RifleMan_Spawn_Blue(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Units/BP_RifleMan_Blue.BP_RifleMan_Blue_C'"));
	if (RifleMan_Spawn_Blue.Succeeded())
		SpawnRifleMan_Blue = RifleMan_Spawn_Blue.Class;
	static ConstructorHelpers::FClassFinder<ASwordMan> SwordMan_Spawn_Blue(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Units/BP_SwordMan_Blue.BP_SwordMan_Blue_C'"));
	if (SwordMan_Spawn_Blue.Succeeded())
		SpawnSwordMan_Blue = SwordMan_Spawn_Blue.Class;
	static ConstructorHelpers::FClassFinder<AMutant> Mutant_Spawn_Blue(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Units/BP_Mutant_Blue.BP_Mutant_Blue_C'"));
	if (Mutant_Spawn_Blue.Succeeded())
		SpawnMutant_Blue = Mutant_Spawn_Blue.Class;

	static ConstructorHelpers::FClassFinder<ARifleMan> RifleMan_Spawn_Red(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Units/BP_RifleMan_Red.BP_RifleMan_Red_C'"));
	if (RifleMan_Spawn_Red.Succeeded())
		SpawnRifleMan_Red = RifleMan_Spawn_Red.Class;
	static ConstructorHelpers::FClassFinder<ASwordMan> SwordMan_Spawn_Red(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Units/BP_SwordMan_Red.BP_SwordMan_Red_C'"));
	if (SwordMan_Spawn_Red.Succeeded())
		SpawnSwordMan_Red = SwordMan_Spawn_Red.Class;
	static ConstructorHelpers::FClassFinder<AMutant> Mutant_Spawn_Red(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Units/BP_Mutant_Red.BP_Mutant_Red_C'"));
	if (Mutant_Spawn_Red.Succeeded())
		SpawnMutant_Red = Mutant_Spawn_Red.Class;

	//스폰할 건물들의 클래스
	static ConstructorHelpers::FClassFinder<ABuilding_Barracks> Spawning_Barracks(TEXT("Class'/Script/TacticalStrike.Building_Barracks'"));
	if (Spawning_Barracks.Succeeded())
		Spawn_Barracks = Spawning_Barracks.Class;
	static ConstructorHelpers::FClassFinder<ABuilding_SynBioLab> Spawning_SynBioLab(TEXT("Class'/Script/TacticalStrike.Building_SynBioLab'"));
	if (Spawning_SynBioLab.Succeeded())
		Spawn_SynBioLab = Spawning_SynBioLab.Class;
	static ConstructorHelpers::FClassFinder<ABuilding_ResourceFacility> Spawning_ResourceFacility(TEXT("Class'/Script/TacticalStrike.Building_ResourceFacility'"));
	if (Spawning_ResourceFacility.Succeeded())
		Spawn_ResourceFacility = Spawning_ResourceFacility.Class;
	static ConstructorHelpers::FClassFinder<ABuilding_EnergyRepeater> Spawning_EnergyRepeater(TEXT("/Script/CoreUObject.Class'/Script/TacticalStrike.Building_EnergyRepeater'"));
	if (Spawning_EnergyRepeater.Succeeded())
		Spawn_EnergyRepeater = Spawning_EnergyRepeater.Class;
}

// Called when the game starts or when spawned
void ADefaultSpawningActor::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACommanderUnit::StaticClass(), CommanderUnitArray);
	//UE_LOG(LogTemp, Log, TEXT("%d"), CommanderUnitArray.Num());
	if (CommanderUnitArray[0]->ActorHasTag("CommanderAI"))
	{
		CommanderAI = Cast<ACommanderAI>(Cast<APawn>(CommanderUnitArray[0])->GetController());
		CommanderController = Cast<ACommanderController>(Cast<APawn>(CommanderUnitArray[1])->GetController());
	}
	else if (CommanderUnitArray[1]->ActorHasTag("CommanderAI"))
	{
		CommanderAI = Cast<ACommanderAI>(Cast<APawn>(CommanderUnitArray[1])->GetController());
		CommanderController = Cast<ACommanderController>(Cast<APawn>(CommanderUnitArray[0])->GetController());
	}

	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));

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

	if (CommanderAI != nullptr && CommanderController != nullptr)
	{
		CommanderController->ResourceProductionDelegate.AddUObject(this, &ADefaultSpawningActor::ResourceProductionComplete);
	}

	//if (SpawnRedCommanderMap != nullptr && SpawnBlueCommanderMap != nullptr)
	//{
	//	SpawnRedCommanderMap->CountPlaceSpawnDelegate.AddDynamic(this, &ADefaultSpawningActor::SpawnUnit);
	//	SpawnBlueCommanderMap->CountPlaceSpawnDelegate.AddDynamic(this, &ADefaultSpawningActor::SpawnUnit);

	//	SpawnRedCommanderMap->SpawnBuildingDelegate.AddDynamic(this, &ADefaultSpawningActor::SpawnBuilding);
	//}

	//if (CommanderController != nullptr)
	//{
	//	CommanderController->ResourceProductionDelegate.AddUObject(this, &ADefaultSpawningActor::ResourceProductionComplete);
	//}

}

void ADefaultSpawningActor::SpawnUnit(FObjectInfo ObjectInfo, ADefaultBuilding* SpawningBuilding)
{
	FVector UnitSpawnLocation = GetSpawnTileLocation(SpawningBuilding);
	//UE_LOG(LogTemp, Log, TEXT("Type: %d"), static_cast<int32>(UnitType));

	if (UnitSpawnLocation == FVector(-100.0f, -100.0f, -100.0f))
		return;
	int32 TileRow = int32(FMath::Floor(UnitSpawnLocation.X / 100));
	int32 TileColumn = int32(FMath::Floor(UnitSpawnLocation.Y / 100));

	ESpawnUnit UnitType = static_cast<ESpawnUnit>(ObjectInfo.ObjectType);

	switch (UnitType)
	{
	case ESpawnUnit::None:
		break;
	case ESpawnUnit::RifleMan:
	{
		if (SpawningBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Blue)
		{
			ARifleMan* RifleMan = GetWorld()->SpawnActor<ARifleMan>(SpawnRifleMan_Blue, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
			RifleMan->ObjectInfo.ObjectOwner = ObjectInfo.ObjectOwner;
			
			ACommanderUnit* CommanderUnit = Cast<ACommanderUnit>(CommanderController->GetPawn());
			ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(RifleMan->GetController());
			if (CommanderUnit != nullptr && DefaultUnitAI != nullptr)
			{
				DefaultUnitAI->GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::MainTeamAIKey, CommanderUnit->TeamMainAIInstance);
				CommanderUnit->TeamMainAIInstance->TeamUnitArr.Add(RifleMan);
			}
			GridActor->SetTile_Unit(FIntPoint(TileRow, TileColumn), Cast<ADefaultUnit>(RifleMan));
		}
		else if (SpawningBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Red)
		{
			ARifleMan* RifleMan = GetWorld()->SpawnActor<ARifleMan>(SpawnRifleMan_Red, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
			RifleMan->ObjectInfo.ObjectOwner = ObjectInfo.ObjectOwner;

			ACommanderUnit* CommanderUnit = Cast<ACommanderUnit>(CommanderAI->GetPawn());
			ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(RifleMan->GetController());

			if (CommanderUnit != nullptr && DefaultUnitAI != nullptr)
			{
				DefaultUnitAI->GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::MainTeamAIKey, CommanderUnit->TeamMainAIInstance);
				CommanderUnit->TeamMainAIInstance->TeamUnitArr.Add(RifleMan);
			}

			GridActor->SetTile_Unit(FIntPoint(TileRow, TileColumn), Cast<ADefaultUnit>(RifleMan));
		}

	}
		break;
	case ESpawnUnit::SwordMan:
	{
		if (SpawningBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Blue)
		{
			ASwordMan* SwordMan = GetWorld()->SpawnActor<ASwordMan>(SpawnSwordMan_Blue, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
			SwordMan->ObjectInfo.ObjectOwner = ObjectInfo.ObjectOwner;

			ACommanderUnit* CommanderUnit = Cast<ACommanderUnit>(CommanderController->GetPawn());
			ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(SwordMan->GetController());

			if (CommanderUnit != nullptr && DefaultUnitAI != nullptr)
			{
				DefaultUnitAI->GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::MainTeamAIKey, CommanderUnit->TeamMainAIInstance);
				CommanderUnit->TeamMainAIInstance->TeamUnitArr.Add(SwordMan);
			}

			GridActor->SetTile_Unit(FIntPoint(TileRow, TileColumn), Cast<ADefaultUnit>(SwordMan));
		}
		else if (SpawningBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Red)
		{
			ASwordMan* SwordMan = GetWorld()->SpawnActor<ASwordMan>(SpawnSwordMan_Red, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
			SwordMan->ObjectInfo.ObjectOwner = ObjectInfo.ObjectOwner;

			ACommanderUnit* CommanderUnit = Cast<ACommanderUnit>(CommanderAI->GetPawn());
			ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(SwordMan->GetController());

			if (CommanderUnit != nullptr && DefaultUnitAI != nullptr)
			{
				DefaultUnitAI->GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::MainTeamAIKey, CommanderUnit->TeamMainAIInstance);
				CommanderUnit->TeamMainAIInstance->TeamUnitArr.Add(SwordMan);
			}

			GridActor->SetTile_Unit(FIntPoint(TileRow, TileColumn), Cast<ADefaultUnit>(SwordMan));
		}
	}
		break;
	case ESpawnUnit::Mutant:
	{
		if (SpawningBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Blue)
		{
			AMutant* Mutant = GetWorld()->SpawnActor<AMutant>(SpawnMutant_Blue, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
			Mutant->ObjectInfo.ObjectOwner = ObjectInfo.ObjectOwner;

			ACommanderUnit* CommanderUnit = Cast<ACommanderUnit>(CommanderController->GetPawn());
			ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(Mutant->GetController());

			if (CommanderUnit != nullptr && DefaultUnitAI != nullptr)
			{
				DefaultUnitAI->GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::MainTeamAIKey, CommanderUnit->TeamMainAIInstance);
				CommanderUnit->TeamMainAIInstance->TeamUnitArr.Add(Mutant);
			}

			GridActor->SetTile_Unit(FIntPoint(TileRow, TileColumn), Cast<ADefaultUnit>(Mutant));
		}
		else if (SpawningBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Red)
		{
			AMutant* Mutant = GetWorld()->SpawnActor<AMutant>(SpawnMutant_Red, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
			Mutant->ObjectInfo.ObjectOwner = ObjectInfo.ObjectOwner;

			ACommanderUnit* CommanderUnit = Cast<ACommanderUnit>(CommanderAI->GetPawn());
			ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(Mutant->GetController());

			if (CommanderUnit != nullptr && DefaultUnitAI != nullptr)
			{
				DefaultUnitAI->GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::MainTeamAIKey, CommanderUnit->TeamMainAIInstance);
				CommanderUnit->TeamMainAIInstance->TeamUnitArr.Add(Mutant);
			}


			GridActor->SetTile_Unit(FIntPoint(TileRow, TileColumn), Cast<ADefaultUnit>(Mutant));
		}
	}
		break;
	default:
		break;
	}
}

FVector ADefaultSpawningActor::GetSpawnTileLocation(ADefaultBuilding* SpawningBuilding)
{
	FVector BuildingLocation = SpawningBuilding->GetActorLocation();


	int32 TileRow = int32(FMath::Floor(BuildingLocation.X / 100));
	int32 TileColumn = int32(FMath::Floor(BuildingLocation.Y / 100));
	FIntPoint SpawnStartLocation = GridActor->GetStartGridTile
	(TileRow, TileColumn, SpawningBuilding->GridSizeX, SpawningBuilding->GridSizeY, SpawningBuilding->ObjectOwner);

	if (SpawningBuilding->ObjectOwner == EObjectOwner::Blue)
	{
		SpawnStartLocation.X--;
	}
	else if (SpawningBuilding->ObjectOwner == EObjectOwner::Red)
	{
		SpawnStartLocation.X++;
	}

	int32 MaxStep = 10;
	int32 CurStep = 0;
	int32 StepLength = SpawningBuilding->GridSizeX + 1;
	int8 dx[4] = {0, 1, 0, -1};
	int8 dy[4] = {1, 0, -1, 0};
	int8 dir = 0;

	FIntPoint SpawnLocation = SpawnStartLocation;

	while (CurStep < MaxStep)
	{
		for (int32 i = 0; i < StepLength; i++)
		{
			if (GridActor->TileCheck(SpawnLocation.X, SpawnLocation.Y))
			{
				if (GridActor->CheckGridObject(SpawnLocation.X, SpawnLocation.Y))
					return FVector(SpawnLocation.X * 100 + 50.0f, SpawnLocation.Y * 100 + 50.0f, 60.0f);
			}
			SpawnLocation.X += dx[dir];
			SpawnLocation.Y += dy[dir];

		}
		dir = (dir + 1) % 4;
		StepLength++;
		CurStep++;
	}

	return FVector(-100.0f, -100.0f, -100.0f);
}

void ADefaultSpawningActor::ResourceProductionComplete(FString Team)
{
	FRotator DefaultRotator = FRotator(0.0f, 0.0f, 0.0f);
	FVector CrystalScale = FVector(200.0f, 200.0f, 300.0f);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	if (Team == "Red")
	{
		if (SpawnRedCommanderMap != nullptr)
		{
			FVector CrystalSpawnLocation = SpawnRedCommanderMap->ResourcePlace->GetComponentLocation() + FVector(400.0f, -400.0f, -200.0f);
			for (float i = CrystalSpawnLocation.X; i < CrystalSpawnLocation.X + 600.0f; i += 200.0f)
			{
				for (float j = CrystalSpawnLocation.Y; j > CrystalSpawnLocation.Y - 1600.0f; j -= 200.0f)
				{
					bool bResult = GetWorld()->OverlapMultiByChannel(
						OverlapResults,
						FVector(i, j, CrystalSpawnLocation.Z),
						FQuat::Identity,
						ECollisionChannel::ECC_GameTraceChannel8,
						FCollisionShape::MakeBox(CrystalScale),
						CollisionQueryParam
					);
					if (bResult)
					{
						DrawDebugBox(GetWorld(), FVector(i, j, 500.0f), CrystalScale, FColor::Red, false, 1.0f);
						continue;
					}
					else
					{
						DrawDebugBox(GetWorld(), FVector(i, j, CrystalSpawnLocation.Z), CrystalScale, FColor::Green, false, 1.0f);
						DefaultBuilding = GetWorld()->SpawnActor<ABuilding_Crystal>(Building_Crystal, FVector(i, j, CrystalSpawnLocation.Z), DefaultRotator);
						UStaticMeshComponent* MeshComponent = DefaultBuilding->FindComponentByClass<UStaticMeshComponent>();
						DefaultBuilding->Tags.Add("RedTeamBuildings");
						if (MeshComponent != nullptr)
							MeshComponent->SetCollisionProfileName(TEXT("Buildings"));
						return;
					}
				}
			}
		}
	}
	else if (Team == "Blue")
	{
		if (SpawnBlueCommanderMap != nullptr)
		{
			FVector CrystalSpawnLocation = SpawnBlueCommanderMap->ResourcePlace->GetComponentLocation() + FVector(-400.0f, 400.0f, -200.0f);
			for (float i = CrystalSpawnLocation.X; i > CrystalSpawnLocation.X - 600.0f; i -= 200.0f)
			{
				for (float j = CrystalSpawnLocation.Y; j < CrystalSpawnLocation.Y + 1600.0f; j += 200.0f)
				{
					bool bResult = GetWorld()->OverlapMultiByChannel(
						OverlapResults,
						FVector(i, j, CrystalSpawnLocation.Z),
						FQuat::Identity,
						ECollisionChannel::ECC_GameTraceChannel8,
						FCollisionShape::MakeBox(CrystalScale),
						CollisionQueryParam
					);
					if (bResult)
					{
						DrawDebugBox(GetWorld(), FVector(i, j, 500.0f), CrystalScale, FColor::Red, false, 1.0f);
						continue;
					}
					else
					{
						DrawDebugBox(GetWorld(), FVector(i, j, CrystalSpawnLocation.Z), CrystalScale, FColor::Green, false, 1.0f);
						DefaultBuilding = GetWorld()->SpawnActor<ABuilding_Crystal>(Building_Crystal, FVector(i, j, CrystalSpawnLocation.Z), DefaultRotator);
						DefaultBuilding->Tags.Add("BlueTeamBuildings");
						UStaticMeshComponent* MeshComponent = DefaultBuilding->FindComponentByClass<UStaticMeshComponent>();
						if (MeshComponent != nullptr)
							MeshComponent->SetCollisionProfileName(TEXT("Buildings"));
						return;
					}
				}
			}


		}
	}
}

void ADefaultSpawningActor::SpawnBuilding(ESpawnBuilding BuildingType, FVector SpawnLocation)
{
	FVector DefaultSpawnLocation = FVector(-50000.0f, -50000.0f, -50000.0f);
	FRotator DefaultRotator = FRotator(0.0f, 180.0f, 0.0f);
	ADefaultBuilding* SpawnDefaultBuilding;

	FVector SetSpawnLocation = SpawnLocation + FVector(-500.0f, 500.0f, 0.0f);


	switch (BuildingType)
	{
	case ESpawnBuilding::Barracks:
		SpawnDefaultBuilding = GetWorld()->SpawnActor<ABuilding_Barracks>(Spawn_Barracks, DefaultSpawnLocation, DefaultRotator);
		break;
	case ESpawnBuilding::SynBioLab:
		SpawnDefaultBuilding = GetWorld()->SpawnActor<ABuilding_SynBioLab>(Spawn_SynBioLab, DefaultSpawnLocation, DefaultRotator);
		break;
	case ESpawnBuilding::ResourceFacility:
		SpawnDefaultBuilding = GetWorld()->SpawnActor<ABuilding_ResourceFacility>(Spawn_ResourceFacility, DefaultSpawnLocation, DefaultRotator);
		break;
	case ESpawnBuilding::EnergyRepeater:
		SpawnDefaultBuilding = GetWorld()->SpawnActor<ABuilding_EnergyRepeater>(Spawn_EnergyRepeater, DefaultSpawnLocation, DefaultRotator);
		break;
	default:
		SpawnDefaultBuilding = GetWorld()->SpawnActor<ABuilding_Barracks>(Spawn_Barracks, DefaultSpawnLocation, DefaultRotator);
		break;
	}
	FVector BuildingSize = FVector::ZeroVector;
	if (SpawnDefaultBuilding != nullptr)
		BuildingSize = GetBuildingScale(SpawnDefaultBuilding);

	//CommanderAI->SetBuildingArr(SpawnDefaultBuilding);

	//TArray<FOverlapResult> OverlapResults;
	//FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);

	//for (int32 i = SetSpawnLocation.X; i > SetSpawnLocation.X - 2500.0f; i -= 100.0f)
	//{
	//	for (int32 j = SetSpawnLocation.Y; j > SetSpawnLocation.Y - 4500.0f; j -= 100.0f)
	//	{
	//		bool bResult = GetWorld()->OverlapMultiByChannel(
	//			OverlapResults,
	//			FVector(i, j, SetSpawnLocation.Z),
	//			FQuat::Identity,
	//			ECollisionChannel::ECC_GameTraceChannel8,
	//			FCollisionShape::MakeBox(BuildingSize),
	//			CollisionQueryParam
	//		);
	//		if (bResult)
	//		{
	//			DrawDebugBox(GetWorld(), FVector(i, j, 500.0f), BuildingSize, FColor::Red, false, 1.0f);
	//			continue;
	//		}
	//		else
	//		{
	//			DrawDebugBox(GetWorld(), FVector(i, j, SetSpawnLocation.Z), BuildingSize, FColor::Green, false, 1.0f);
	//			SpawnDefaultBuilding->SetActorLocation(FVector(i, j, SetSpawnLocation.Z));
	//			//UStaticMeshComponent* MeshComponent = SpawnDefaultBuilding->FindComponentByClass<UStaticMeshComponent>();
	//			SpawnDefaultBuilding->Tags.Add("RedTeamBuildings");
	//			//if (MeshComponent != nullptr)
	//			//	MeshComponent->SetCollisionProfileName(TEXT("Buildings"));
	//			return;
	//		}
	//	}
	//}

}

FVector ADefaultSpawningActor::GetBuildingScale(ADefaultBuilding* BuildingInfo)
{
	UStaticMeshComponent* StaticMeshComp = BuildingInfo->FindComponentByClass<UStaticMeshComponent>();
	FVector BuildingScale = BuildingInfo->GetActorScale();
	FVector BuildingSizeMin;
	FVector BuildingSizeMax;
	StaticMeshComp->GetLocalBounds(BuildingSizeMin, BuildingSizeMax);

	FVector BuildingSize = BuildingSizeMax * BuildingScale;
	BuildingSize = FVector(BuildingSize.X + 100.0f, BuildingSize.Y + 100.0f, BuildingSize.Z + 100.0f);
	return BuildingSize;
}

