// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Buildings/Building_EnergyRepeater.h"

ABuilding_EnergyRepeater::ABuilding_EnergyRepeater()
{
	BuildingType = 121;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingEnergyRepeater(TEXT("/Script/Engine.StaticMesh'/Game/HoverVehicles/Meshes/Things/SM_LampPole.SM_LampPole'"));
	if (BuildingEnergyRepeater.Succeeded())
		DefaultBuildingMesh->SetStaticMesh(BuildingEnergyRepeater.Object);

	/*if (GameInstance != nullptr)
		DefaultBuildingMat = GameInstance->BasicMat_EnergyRepeater;*/
}

void ABuilding_EnergyRepeater::BeginPlay()
{
	Super::BeginPlay();

	DefaultBuildingMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.15f));
}
