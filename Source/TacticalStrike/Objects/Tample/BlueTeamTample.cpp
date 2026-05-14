// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueTeamTample.h"
//#include "TacticalStrikeGameStateBase.h"
#include "Kismet/GameplayStatics.h"
//#include "CommanderMap.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABlueTeamTample::ABlueTeamTample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlueTeamTampleMesh"));

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BlueTeamTampleMesh(TEXT("StaticMesh'/Game/Isometric_World/EditMeshes/SM_MERGED_SM_Temple_Core_4.SM_MERGED_SM_Temple_Core_4'"));
	//if (BlueTeamTampleMesh.Succeeded())
	//{
	//	Mesh->SetStaticMesh(BlueTeamTampleMesh.Object);
	//}

	//static ConstructorHelpers::FClassFinder<ARifleMan> RifleMan_Spawn(TEXT("Blueprint'/Game/Blueprints/Units/BP_RifleMan_Blue.BP_RifleMan_Blue_C'"));
	//if (RifleMan_Spawn.Succeeded())
	//	SpawnRifleMan = RifleMan_Spawn.Class;
	//static ConstructorHelpers::FClassFinder<ASwordMan> SwordMan_Spawn(TEXT("Blueprint'/Game/Blueprints/Units/BP_SwordMan_Blue.BP_SwordMan_Blue_C'"));
	//if (SwordMan_Spawn.Succeeded())
	//	SpawnSwordMan = SwordMan_Spawn.Class;
	//static ConstructorHelpers::FClassFinder<AMutant> Mutant_Spawn(TEXT("Blueprint'/Game/Blueprints/Units/BP_Mutant_Blue.BP_Mutant_Blue_C'"));
	//if (Mutant_Spawn.Succeeded())
	//	SpawnMutant = Mutant_Spawn.Class;

	//Health = 12000;
	//Armor = 12;
	TampleColor = "Blue";
	DefaultBuildingMesh->SetCollisionProfileName(TEXT("BlueTeamBuilding"));
	//RifleManStr = "Blueprint'/Game/Blueprints/Units/BP_RifleMan_Blue.BP_RifleMan_Blue_C'";
	//SwordManStr = "Blueprint'/Game/Blueprints/Units/BP_SwordMan_Blue.BP_SwordMan_Blue_C'";
	//MutantStr = "Blueprint'/Game/Blueprints/Units/BP_Mutant_Blue.BP_Mutant_Blue_C'";
	//InitUnitClass(RifleManStr, SwordManStr, MutantStr);

	ObjectInfo.ObjectOwner = EObjectOwner::Blue;
	ObjectOwner = EObjectOwner::Blue;
}

void ABlueTeamTample::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add("BlueTeamBuilding");
	this->Tags.Add("BlueTeamTample");
	//GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//if (GameInstance != nullptr)
	//{
	//	BuildingDataInfo = GameInstance->GetBuildingTable(BuildingType);
	//	if (BuildingDataInfo != nullptr)
	//	{
	//		DefaultHP = BuildingDataInfo->MaxHP;
	//		CurrentHP = BuildingDataInfo->MaxHP;
	//		Armor = BuildingDataInfo->Armor;
	//	}
	//}

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACommanderMap::StaticClass(), SpawnUnitArray);
	//if (SpawnUnitArray[0]->ActorHasTag("BlueTeamMap"))
	//{
	//	SpawnCommanderMap = Cast<ACommanderMap>(SpawnUnitArray[0]);
	//	if (SpawnCommanderMap != nullptr)
	//	{
	//		SpawnCommanderMap->UnitSpawnDelegate.AddDynamic(this, &ABlueTeamTample::GetUnitArray);
	//	}
	//}
	//else if (SpawnUnitArray[1]->ActorHasTag("BlueTeamMap"))
	//{
	//	SpawnCommanderMap = Cast<ACommanderMap>(SpawnUnitArray[1]);
	//	if (SpawnCommanderMap != nullptr)
	//	{
	//		SpawnCommanderMap->UnitSpawnDelegate.AddDynamic(this, &ABlueTeamTample::GetUnitArray);
	//	}
	//}

	//SpawnBlueUnit = GetWorld() != NULL ? GetWorld()->GetGameState<ATacticalStrikeGameStateBase>() : NULL;
	//if (SpawnBlueUnit != nullptr)
	//{
	//	SpawnBlueUnit->WorldUnitSpawnTrigger.AddDynamic(this, &ABlueTeamTample::GetUnitArray);
	//}
}

/*
void ABlueTeamTample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}*/

//사용 x, 다른 곳에서 처리
//void ABlueTeamTample::GetUnitArray()
//{
//	//Super::GetUnitArray();
//	TampleUnitSpawnLocation = GetActorLocation() + FVector(1500.0f, 300.0f, 100.0f);
//	ADefaultTample::GetUnitArray();
//	//UE_LOG(LogTemp, Log, TEXT("nu m: %d"), SpawnCommanderMap->UnitsArray[0]->UnitCount);
//	
//
//	////유닛 소환 전 해당 위치에 트레이스 판정, 다른 유닛이 없을 시 유닛 스폰
//	//TArray<FOverlapResult> OverlapResults;
//	//FVector UnitSpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 0.0f);
//	////FVector UnitSpawnScale = FVector(80.0f, 80.0f, 100.0f);
//	//FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
//
//	////소환할 유닛이 없으면 리턴
//	//if (SpawnCommanderMap->UnitsArray.Num() == 0)
//	//	return;
//
//	////for (uint8 n = 0; n < SpawnCommanderMap->UnitsArray.Num(); n++)
//	////{
//	////	UE_LOG(LogTemp, Log, TEXT("Type:  %d"), SpawnCommanderMap->UnitsArray[n]->UnitType);
//	////	UE_LOG(LogTemp, Log, TEXT("Count:  %d"), SpawnCommanderMap->UnitsArray[n]->UnitCount);
//	////}
//
//	//for (uint8 k = 0; k < SpawnCommanderMap->UnitsArray.Num(); k++)
//	//{
//	//	FVector SpawnUnitScale = CheckUnitSpawnScale(SpawnCommanderMap->UnitsArray[k]);
//	//	uint32 CountNumber = 0;
//
//	//	for (int32 i = UnitSpawnLocation.X; i > 200; i -= 40)
//	//	{
//	//		for (uint32 j = UnitSpawnLocation.Y; j < 5500; j += 40)
//	//		{
//	//			bool bResult = GetWorld()->OverlapMultiByChannel(
//	//				OverlapResults,
//	//				FVector(i, j, 100.0f),
//	//				FQuat::Identity,
//	//				ECollisionChannel::ECC_GameTraceChannel5,
//	//				FCollisionShape::MakeBox(SpawnUnitScale),
//	//				CollisionQueryParam
//	//			);
//	//			if (bResult)
//	//			{
//	//				DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Green, false, 1.0f);
//	//				continue;
//	//			}
//	//			else
//	//			{
//	//				if (SpawnCommanderMap->UnitsArray[k]->UnitCount <= CountNumber)
//	//				{
//	//					continue;
//	//				}
//
//	//				DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Red, false, 1.0f);
//	//				SpawnUnit(SpawnCommanderMap->UnitsArray[k], FVector(i, j, 100.0f));
//	//				CountNumber++;
//	//			}
//	//		}
//	//	}
//	//}
//
//	//SpawnCommanderMap->UnitsArray.Empty();
//	//TArray<AActor*> RifleManArray;
//	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARifleMan::StaticClass(), RifleManArray);
//	//UE_LOG(LogTemp, Log, TEXT("RifleMan: %d"), RifleManArray.Num());
//}
//사용 x, 다른 곳에서 처리
//void ABlueTeamTample::SpawnUnit(UUnitsArray* UnitsInfo, FVector UnitSpawnLocation)
//{
//	//ADefaultUnit* SpawnDefaultUnit;
//	//switch (UnitsInfo->UnitType)
//	//{
//	//case 1:
//	//	SpawnDefaultUnit = GetWorld()->SpawnActor<ARifleMan>(SpawnRifleMan, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
//	//	break;
//	//case 2:
//	//	SpawnDefaultUnit = GetWorld()->SpawnActor<ASwordMan>(SpawnSwordMan, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
//	//	break;
//	//case 3:
//	//	SpawnDefaultUnit = GetWorld()->SpawnActor<AMutant>(SpawnMutant, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
//	//default:
//	//	return;
//	//}
//	//SpawnDefaultUnit->Tags.Add(TEXT("BlueTeamUnit"));
//
//	TampleColor = "Blue";
//	ADefaultTample::SpawnUnit(UnitsInfo, UnitSpawnLocation);
//}
//사용 x, 다른 곳에서 처리
//FVector ABlueTeamTample::CheckUnitSpawnScale(UUnitsArray* UnitsInfo)
//{
//	//switch (UnitsInfo->UnitType)
//	//{
//	//case 1:
//	//	return FVector(40.0f, 40.0f, 50.0f);
//	//case 2:
//	//	return FVector(40.0f, 40.0f, 50.0f);
//	//case 3:
//	//	return FVector(80.0f, 80.0f, 100.0f);
//	//default:
//	//	return FVector(0, 0, 0);
//	//}
//	//TScriptInterface<ITacticalStrikeInterface> Interface = NewObject<UInterfaceImplementer>();
//	//if (Interface)
//	//{
//	//	FVector ReturnVector = ITacticalStrikeInterface::Execute_CheckUnitSpawnScale(this, UnitsInfo);
//	//	//FVector ReturnVector = Interface->Excute_CheckUnitSpawnScale(UnitsInfo);
//	//	UE_LOG(LogTemp, Log, TEXT("%f, %f, %f"), ReturnVector.X, ReturnVector.Y, ReturnVector.Z);
//	//	return ReturnVector;
//	//}
//	FVector ReturnVector = FVector(30.0f, 30.0f, 30.0f);
//	if (this->GetClass()->ImplementsInterface(UTacticalStrikeInterface::StaticClass()))
//	{
//		//UE_LOG(LogTemp, Log, TEXT("fffffxzxxxttttttttttx"));
//		//ReturnVector = ITacticalStrikeInterface::Execute_CheckUnitSpawnScale(this, UnitsInfo);
//		Cast<ITacticalStrikeInterface>(this)->TestInter();
//	}
//	UE_LOG(LogTemp, Log, TEXT("%f, %f, %f"), ReturnVector.X, ReturnVector.Y, ReturnVector.Z);
//	return FVector(0.0f, 0.0f, 0.0f);
//}
