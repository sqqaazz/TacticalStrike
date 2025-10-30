// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultTample.h"
#include "GameMode/TacticalStrikeGameInstance.h"
//#include "TacticalStrikeGameStateBase.h"
#include "Kismet/GameplayStatics.h"
//#include "UnitsArray.h"
#include "DrawDebugHelpers.h"
//#include "CommanderMap.h"

ADefaultTample::ADefaultTample()
{
	PrimaryActorTick.bCanEverTick = false;
	BuildingType = 201;
	TampleColor = "";
	//TampleUnitSpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TampleMesh(TEXT("StaticMesh'/Game/Isometric_World/EditMeshes/SM_MERGED_SM_Temple_Core_4.SM_MERGED_SM_Temple_Core_4'"));
	if (TampleMesh.Succeeded())
	{
		DefaultBuildingMesh->SetStaticMesh(TampleMesh.Object);
	}

	//DefaultBuildingMesh->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
}

//void ADefaultTample::InitUnitClass(const FString& NewRifleManText, const FString& NewSwordManText, const FString& NewMutantText)
//{
//	UE_LOG(LogTemp, Log, TEXT("%s"), *NewRifleManText);
//	UE_LOG(LogTemp, Log, TEXT("%s"), *NewSwordManText);
//	UE_LOG(LogTemp, Log, TEXT("%s"), *NewMutantText);
//
//	static ConstructorHelpers::FClassFinder<ARifleMan> RifleMan_Spawn(*NewRifleManText);
//	if (RifleMan_Spawn.Succeeded())
//		SpawnRifleMan = RifleMan_Spawn.Class;
//	static ConstructorHelpers::FClassFinder<ASwordMan> SwordMan_Spawn(*NewSwordManText);
//	if (SwordMan_Spawn.Succeeded())
//		SpawnSwordMan = SwordMan_Spawn.Class;
//	static ConstructorHelpers::FClassFinder<AMutant> Mutant_Spawn(*NewMutantText);
//	if (Mutant_Spawn.Succeeded())
//		SpawnMutant = Mutant_Spawn.Class;
//}

void ADefaultTample::BeginPlay()
{
	Super::BeginPlay();

	//GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//if (GameInstance != nullptr)
	//{
	//	BuildingDataInfo = GameInstance->GetBuildingTable(BuildingType);

	//	if (BuildingDataInfo != nullptr)
	//	{
	//		//BuildingName = UnitDataInfo->Name;
	//		//Attack = UnitDataInfo->Attack;
	//		Armor = BuildingDataInfo->Armor;
	//		DefaultHP = BuildingDataInfo->MaxHP;
	//		CurrentHP = DefaultHP;
	//		GridSizeX = BuildingDataInfo->GridSizeX;
	//		GridSizeY = BuildingDataInfo->GridSizeY;
	//		//UE_LOG(LogTemp, Log, TEXT("TampleScale: %d, %f"), DefaultHP, float(GridSizeY) * 100.0f);
	//	}
	//	SetBuildingScale();
	//	//SetActorScale3D(FVector(10.0f, 10.0f, 10.0f));
	SetActorScale3D(FVector(0.7f, 0.7f, 0.7f));
	//DefaultBuildingMesh->SetCollisionProfileName(TEXT("Building"));
	ObjectInfo.ObjectState = EObjectState::Activated;
	ObjectState = EObjectState::Activated;
}

void ADefaultTample::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	if (GridActor != nullptr)
	{
		FIntPoint TampleGrid = GridActor->GetGridTile(GetActorLocation());
		if (GridActor->TileCheck(TampleGrid.X, TampleGrid.Y))
		{
			GridActor->SetTile_Building(TampleGrid, this, true);
			//UE_LOG(LogTemp, Log, TEXT("Code: %d"), BuildingType);
		}
	}
}

float ADefaultTample::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHP = FMath::Clamp(int32(CurrentHP - (FinalDamage - Armor)), 0, DefaultHP);
	OnBuildingHPChanged.Broadcast();
	//OnBuildingHPChanged.Broadcast(this);
	return FinalDamage;
}

//유닛 카운트 장소에서 유닛 체크 후 필드에 스폰
//void ADefaultTample::GetUnitArray()
//{
//	//유닛 소환 전 해당 위치에 트레이스 판정, 다른 유닛이 없을 시 유닛 스폰
//	TArray<FOverlapResult> OverlapResults;
//	//FVector UnitSpawnLocation = GetActorLocation() + FVector(0.0f, 2000.0f, 100.0f);
//	FVector UnitSpawnLocation = TampleUnitSpawnLocation;
//	//FVector UnitSpawnScale = FVector(80.0f, 80.0f, 100.0f);
//	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
//
//	//소환할 유닛이 없으면 리턴
//	if (SpawnCommanderMap->UnitsArray.Num() == 0)
//		return;
//
//	for (uint8 k = 0; k < SpawnCommanderMap->UnitsArray.Num(); k++)
//	{
//		FVector SpawnUnitScale = CheckUnitSpawnScale(SpawnCommanderMap->UnitsArray[k]);
//		uint32 CountNumber = 0;
//
//		if (TampleColor == "Blue")
//		{
//			for (int32 i = UnitSpawnLocation.X; i > (UnitSpawnLocation.X - 1800.0f); i -= 40)
//			{
//				for (uint32 j = UnitSpawnLocation.Y; j < (UnitSpawnLocation.Y + 1800.0f); j += 40)
//				{
//					bool bResult = GetWorld()->OverlapMultiByChannel(
//						OverlapResults,
//						FVector(i, j, 100.0f),
//						FQuat::Identity,
//						ECollisionChannel::ECC_GameTraceChannel5,
//						FCollisionShape::MakeBox(SpawnUnitScale),
//						CollisionQueryParam
//					);
//					if (bResult)
//					{
//						DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Green, false, 1.0f);
//						continue;
//					}
//					else
//					{
//						if (SpawnCommanderMap->UnitsArray[k]->UnitCount <= CountNumber)
//						{
//							continue;
//						}
//
//						DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Red, false, 1.0f);
//						SpawnUnit(SpawnCommanderMap->UnitsArray[k], FVector(i, j, 100.0f));
//						CountNumber++;
//					}
//				}
//			}
//		}
//		else if (TampleColor == "Red")
//		{
//			for (int32 i = UnitSpawnLocation.X; i < (UnitSpawnLocation.X + 1800.0f); i += 40)
//			{
//				for (uint32 j = UnitSpawnLocation.Y; j > (UnitSpawnLocation.Y - 1800.0f); j -= 40)
//				{
//					bool bResult = GetWorld()->OverlapMultiByChannel(
//						OverlapResults,
//						FVector(i, j, 100.0f),
//						FQuat::Identity,
//						ECollisionChannel::ECC_GameTraceChannel5,
//						FCollisionShape::MakeBox(SpawnUnitScale),
//						CollisionQueryParam
//					);
//					if (bResult)
//					{
//						DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Green, false, 1.0f);
//						continue;
//					}
//					else
//					{
//						if (SpawnCommanderMap->UnitsArray[k]->UnitCount <= CountNumber)
//							continue;
//
//						DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Red, false, 1.0f);
//						SpawnUnit(SpawnCommanderMap->UnitsArray[k], FVector(i, j, 100.0f));
//						CountNumber++;
//					}
//				}
//			}
//		}
//
//		//for (int32 i = UnitSpawnLocation.X; i > 200; i -= 40)
//		//{
//		//	for (uint32 j = UnitSpawnLocation.Y; j < 5500; j += 40)
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
//		//			{
//		//				continue;
//		//			}
//
//		//			DrawDebugBox(GetWorld(), FVector(i, j, 100.0f), SpawnUnitScale, FColor::Red, false, 1.0f);
//		//			SpawnUnit(SpawnCommanderMap->UnitsArray[k], FVector(i, j, 100.0f));
//		//			CountNumber++;
//		//		}
//		//	}
//		//}
//	}
//	SpawnCommanderMap->UnitsArray.Empty();
//}

//void ADefaultTample::SpawnUnit(UUnitsArray* UnitsInfo, FVector UnitSpawnLocation)
//{
//	ADefaultUnit* SpawnDefaultUnit;
//	switch (UnitsInfo->UnitType)
//	{
//	case 1:
//		SpawnDefaultUnit = GetWorld()->SpawnActor<ARifleMan>(SpawnRifleMan, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
//		break;
//	case 2:
//		SpawnDefaultUnit = GetWorld()->SpawnActor<ASwordMan>(SpawnSwordMan, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
//		break;
//	case 3:
//		SpawnDefaultUnit = GetWorld()->SpawnActor<AMutant>(SpawnMutant, UnitSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
//		break;
//	default:
//		return;
//	}
//
//	if (TampleColor != "" && SpawnDefaultUnit  != nullptr)
//	{
//		if (TampleColor == "Red")
//			SpawnDefaultUnit->Tags.Add(TEXT("RedTeamUnit"));
//		else if (TampleColor == "Blue")
//			SpawnDefaultUnit->Tags.Add(TEXT("BlueTeamUnit"));
//		else
//			return;
//	}
//}
//
//FVector ADefaultTample::CheckUnitSpawnScale(UUnitsArray* UnitsInfo)
//{
//	switch (UnitsInfo->UnitType)
//	{
//	case 1:
//		return FVector(40.0f, 40.0f, 50.0f);
//	case 2:
//		return FVector(40.0f, 40.0f, 50.0f);
//	case 3:
//		return FVector(80.0f, 80.0f, 100.0f);
//	default:
//		return FVector(0.0f, 0.0f, 0.0f);
//	}
//	//return FVector(0.0f, 0.0f, 0.0f);
//}
