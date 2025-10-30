// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_ResourceFacility.h"
//#include "TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"

ABuilding_ResourceFacility::ABuilding_ResourceFacility()
{
	PrimaryActorTick.bCanEverTick = false;
	BuildingType = 202;
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//DefaultBuildingMesh->SetStaticMesh(GameInstance->StaticMesh_SynBioLab);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingResourceFacility(TEXT("StaticMesh'/Game/3DModels/Buildings/MRowaBuildings/coal-power-station/source/CoalPowerStation/CoalPowerStation_Merge_CoalPowerStation_MainDoor.CoalPowerStation_Merge_CoalPowerStation_MainDoor'"));
	if (BuildingResourceFacility.Succeeded())
	{
		DefaultBuildingMesh->SetStaticMesh(BuildingResourceFacility.Object);
	}

	if (GameInstance != nullptr)
		DefaultBuildingMat = GameInstance->BasicMat_ResourceFacility;

	DefaultBuildingMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	DefaultBuildingMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	///DefaultBuildingMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
}
