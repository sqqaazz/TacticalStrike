// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_SynBioLab.h"
//#include "TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"

ABuilding_SynBioLab::ABuilding_SynBioLab()
{
	PrimaryActorTick.bCanEverTick = false;
	BuildingType = 102;
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//DefaultBuildingMesh->SetStaticMesh(GameInstance->StaticMesh_SynBioLab);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingSynBioLab(TEXT("StaticMesh'/Game/3DModels/Buildings/MRowaBuildings/jewelry-factory/source/JewelryFactory_Merge_JewelryFactory_Parts.JewelryFactory_Merge_JewelryFactory_Parts'"));
	if (BuildingSynBioLab.Succeeded())
	{
		DefaultBuildingMesh->SetStaticMesh(BuildingSynBioLab.Object);
	}

	if (GameInstance != nullptr)
		DefaultBuildingMat = GameInstance->BasicMat_SynBioLab;

	DefaultBuildingMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	DefaultBuildingMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	//DefaultBuildingMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
}
