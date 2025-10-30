// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_Barracks.h"
//#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABuilding_Barracks::ABuilding_Barracks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BuildingType = 101;
	//GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingBarracks(TEXT("StaticMesh'/Game/3DModels/StaticMesh/Buildings/Barracks/rts-military-building-1/SM_MERGED_Barracks_build_19.SM_MERGED_Barracks_build_19'"));
	if (BuildingBarracks.Succeeded())
		DefaultBuildingMesh->SetStaticMesh(BuildingBarracks.Object);

	if (GameInstance != nullptr)
		DefaultBuildingMat = GameInstance->BasicMat_Barracks;


	//DefaultBuildingMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	DefaultBuildingMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	//DefaultBuildingMesh->SetRelativeScale3D(FVector(7.0f, 7.0f, 7.0f));
	//BarracksMesh->SetCollisionProfileName(TEXT("NoCollision"));

	GetBuildingMaterial();
}

//void ABuilding_Barracks::BeginPlay()
//{
//	Super::BeginPlay();
//	
//
//	/*this->Tags.Add("Building");*/
//}

void ABuilding_Barracks::SetEnableMat()
{
	DefaultBuildingMesh->SetMaterial(0, BuildEnableMat);
	DefaultBuildingMesh->SetMaterial(1, BuildEnableMat);
	DefaultBuildingMesh->SetMaterial(2, BuildEnableMat);
}

void ABuilding_Barracks::SetDisableMat()
{
	DefaultBuildingMesh->SetMaterial(0, BuildDisableMat);
	DefaultBuildingMesh->SetMaterial(1, BuildDisableMat);
	DefaultBuildingMesh->SetMaterial(2, BuildDisableMat);
}

void ABuilding_Barracks::SetBasicMat()
{
	DefaultBuildingMesh->SetMaterial(0, DefaultBuildingMat);
	DefaultBuildingMesh->SetMaterial(1, LeftDoorMat);
	DefaultBuildingMesh->SetMaterial(2, RightDoorMat);
	DefaultBuildingMesh->SetCollisionProfileName(TEXT("Buildings"));
}

void ABuilding_Barracks::GetBuildingMaterial()
{
	LeftDoorMat = DefaultBuildingMesh->GetMaterial(1);
	RightDoorMat = DefaultBuildingMesh->GetMaterial(2);
}

