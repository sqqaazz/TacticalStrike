// Fill out your copyright notice in the Description page of Project Settings.


#include "RedTeamTample.h"
//#include "TacticalStrikeGameStateBase.h"
#include "Kismet/GameplayStatics.h"
//#include "CommanderMap.h"
#include "DrawDebugHelpers.h"

// Sets default values
ARedTeamTample::ARedTeamTample()
{
	PrimaryActorTick.bCanEverTick = false;

	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RedTeamTampleMesh"));

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> RedTeamTampleMesh(TEXT("StaticMesh'/Game/Isometric_World/EditMeshes/SM_MERGED_SM_Temple_Core_4.SM_MERGED_SM_Temple_Core_4'"));
	//if (RedTeamTampleMesh.Succeeded())
	//{
	//	Mesh->SetStaticMesh(RedTeamTampleMesh.Object);
	//}

	//static ConstructorHelpers::FClassFinder<ARifleMan> RifleMan_Spawn(TEXT("Blueprint'/Game/Blueprints/Units/BP_RifleMan_Red.BP_RifleMan_Red_C'"));
	//if (RifleMan_Spawn.Succeeded())
	//	SpawnRifleMan = RifleMan_Spawn.Class;
	//static ConstructorHelpers::FClassFinder<ASwordMan> SwordMan_Spawn(TEXT("Blueprint'/Game/Blueprints/Units/BP_SwordMan_Red.BP_SwordMan_Red_C'"));
	//if (SwordMan_Spawn.Succeeded())
	//	SpawnSwordMan = SwordMan_Spawn.Class;
	//static ConstructorHelpers::FClassFinder<AMutant> Mutant_Spawn(TEXT("Blueprint'/Game/Blueprints/Units/BP_Mutant_Red.BP_Mutant_Red_C'"));
	//if (Mutant_Spawn.Succeeded())
	//	SpawnMutant = Mutant_Spawn.Class;

	//Health = 12000;
	//Armor = 12;
	TampleColor = "Red";

	DefaultBuildingMesh->SetCollisionProfileName(TEXT("RedTeamBuilding"));
	//RifleManStr = "Blueprint'/Game/Blueprints/Units/BP_RifleMan_Red.BP_RifleMan_Red_C'";
	//SwordManStr = "Blueprint'/Game/Blueprints/Units/BP_SwordMan_Red.BP_SwordMan_Red_C'";
	//MutantStr = "Blueprint'/Game/Blueprints/Units/BP_Mutant_Red.BP_Mutant_Red_C'";
	//InitUnitClass(RifleManStr, SwordManStr, MutantStr);

	ObjectInfo.ObjectOwner = EObjectOwner::Red;
	ObjectOwner = EObjectOwner::Red;
}

// Called when the game starts or when spawned
void ARedTeamTample::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add("RedTeamBuilding");
	this->Tags.Add("RedTeamTample");
	/*SpawnRedUnit = GetWorld() != NULL ? GetWorld()->GetGameState<ATacticalStrikeGameStateBase>() : NULL;
	if (SpawnRedUnit != nullptr)
	{
		SpawnRedUnit->WorldUnitSpawnTrigger.AddDynamic(this, &ARedTeamTample::SpawnUnit);
	}*/
	/*GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance != nullptr)
	{
		BuildingDataInfo = GameInstance->GetBuildingTable(BuildingType);
		if (BuildingDataInfo != nullptr)
		{
			DefaultHP = BuildingDataInfo->MaxHP;
			CurrentHP = BuildingDataInfo->MaxHP;
			Armor = BuildingDataInfo->Armor;
		}
	}*/

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACommanderMap::StaticClass(), SpawnUnitArray);
	//if (SpawnUnitArray[0]->ActorHasTag("RedTeamMap"))
	//{
	//	SpawnCommanderMap = Cast<ACommanderMap>(SpawnUnitArray[0]);
	//	if (SpawnCommanderMap != nullptr)
	//	{
	//		SpawnCommanderMap->UnitSpawnDelegate.AddDynamic(this, &ARedTeamTample::GetUnitArray);
	//	}
	//}
	//else if (SpawnUnitArray[1]->ActorHasTag("RedTeamMap"))
	//{
	//	SpawnCommanderMap = Cast<ACommanderMap>(SpawnUnitArray[1]);
	//	if (SpawnCommanderMap != nullptr)
	//	{
	//		SpawnCommanderMap->UnitSpawnDelegate.AddDynamic(this, &ARedTeamTample::GetUnitArray);
	//	}
	//}
}

//void ARedTeamTample::GetUnitArray()
//{
//	//UE_LOG(LogTemp, Log, TEXT("nu m: %d"), SpawnCommanderMap->UnitsArray[0]->UnitCount);
//	/*Super::GetUnitArray();*/
//	TampleUnitSpawnLocation = GetActorLocation() + FVector(-1500.0f, -300.0f, 100.0f);
//	ADefaultTample::GetUnitArray();
//
//	////유닛 소환 전 해당 위치에 트레이스 판정, 다른 유닛이 없을 시 유닛 스폰
//	//TArray<FOverlapResult> OverlapResults;
//	//FVector UnitSpawnLocation = GetActorLocation() + FVector(1500.0f, -300.0f, 100.0f);
//	////FVector UnitSpawnScale = FVector(80.0f, 80.0f, 100.0f);
//	//FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
//
//	////소환할 유닛이 없으면 리턴
//	//if (SpawnCommanderMap->UnitsArray.Num() == 0)
//	//	return;
//
//	//for (uint8 k = 0; k < SpawnCommanderMap->UnitsArray.Num(); k++)
//	//{
//	//	FVector SpawnUnitScale = CheckUnitSpawnScale(SpawnCommanderMap->UnitsArray[k]);
//	//	uint32 CountNumber = 0;
//
//		//for (int32 i = UnitSpawnLocation.X; i < 11600; i += 40)
//		//{
//		//	for (uint32 j = UnitSpawnLocation.Y; j > 200; j -= 40)
//		//	{
//		//		bool bResult = GetWorld()->OverlapMultiByChannel(
//		//			OverlapResults,
//		//			FVector(i, j, 100.0f),
//		//			FQuat::Identity,
//		//			ECollisionChannel::ECC_GameTraceChannel5,
//		//			FCollisionShape::MakeBox(SpawnUnitScale),
//		//			CollisionQueryParam
//		//		);
//		//		if (bResult)
//		//		{
//		//			DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Green, false, 1.0f);
//		//			continue;
//		//		}
//		//		else
//		//		{
//		//			if (SpawnCommanderMap->UnitsArray[k]->UnitCount <= CountNumber)
//		//				continue;
//
//		//			DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Red, false, 1.0f);
//		//			SpawnUnit(SpawnCommanderMap->UnitsArray[k], FVector(i, j, 100.0f));
//		//			CountNumber++;
//		//		}
//		//	}
//		//}
//	//}
//
//	//SpawnCommanderMap->UnitsArray.Empty();
//	//TArray<AActor*> RifleManArray;
//	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARifleMan::StaticClass(), RifleManArray);
//	//UE_LOG(LogTemp, Log, TEXT("RifleMan: %d"), RifleManArray.Num());
//}

//void ARedTeamTample::SpawnUnit(UUnitsArray* UnitsInfo, FVector UnitSpawnLocation)
//{
//	TampleColor = "Red";
//	ADefaultTample::SpawnUnit(UnitsInfo, UnitSpawnLocation);
//}