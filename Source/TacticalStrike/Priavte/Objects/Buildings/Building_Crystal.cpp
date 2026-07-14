// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Buildings/Building_Crystal.h"
#include "Widgets/ObjectHealthWidget.h"
#include "Components/WidgetComponent.h"

ABuilding_Crystal::ABuilding_Crystal()
{
	PrimaryActorTick.bCanEverTick = false;
	BuildingType = 131;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingCrystal(TEXT("StaticMesh'/Game/3DModels/StaticMesh/Crystal/crystals/source/Crystals_SM.Crystals_SM'"));
	if (BuildingCrystal.Succeeded())
		DefaultBuildingMesh->SetStaticMesh(BuildingCrystal.Object);

	//if (GameInstance != nullptr)
	//	DefaultBuildingMat = GameInstance->BasicMat_Barracks;

	//DefaultBuildingMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	//DefaultBuildingMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	//DefaultBuildingMesh->SetRelativeScale3D(FVector(40.0f, 40.0f, 40.0f));
}

void ABuilding_Crystal::BeginPlay()
{
	Super::BeginPlay();

	DefaultBuildingMesh->SetRelativeScale3D(FVector(2.0f));
	HPBarWidget->SetVisibility(false);
}