// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Buildings/Building_GatheringResource.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Objects/GridActor.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Buildings/Building_Crystal.h"
#include "Components/SpawnResourceComponent.h"
#include "Components/GridTileActor.h"

ABuilding_GatheringResource::ABuilding_GatheringResource()
{
	BuildingType = 104;

	NiagaraComponent_Range = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_ResourceGathering_Range"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingResourceGathering(TEXT("/Script/Engine.StaticMesh'/Game/3DModels/Buildings/MRowaBuildings/smeltery/source/Smeltery_Merge_Smeltery_UpperBody.Smeltery_Merge_Smeltery_UpperBody'"));
	if (BuildingResourceGathering.Succeeded())
		DefaultBuildingMesh->SetStaticMesh(BuildingResourceGathering.Object);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraRange(TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/Niagara/Niagara_Range.Niagara_Range'"));
	if (NiagaraRange.Succeeded())
	{
		//NiagaraSystem_ObjectSelected = Selected.Object;
		NiagaraComponent_Range->SetAsset(NiagaraRange.Object);
		NiagaraComponent_Range->bAutoActivate = true;
	}

	NiagaraComponent_Range->SetupAttachment(RootScene);

	GatheringRange = 1500.0f;
}

void ABuilding_GatheringResource::BeginPlay()
{
	Super::BeginPlay();

	//DefaultBuildingMesh->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));

	//GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	SetNiagaraRange(GatheringRange);
}

//void ABuilding_GatheringResource::SetBuildingScale()
//{
//	Super::SetBuildingScale();
//
//	FVector OriginalSize = DefaultBuildingMesh->Bounds.BoxExtent * 2.0f;
//	if (OriginalSize.IsNearlyZero())
//		return;
//	float DefaultScaleX = (float(GridSizeX) * 100.0f) / OriginalSize.X;
//	float DefaultScaleY = (float(GridSizeY) * 100.0f) / OriginalSize.Y;
//	float AspectRatioZ = OriginalSize.Z / ((OriginalSize.X + OriginalSize.Y) * 1.0f);
//	float DefaultScaleZ = ((DefaultScaleX + DefaultScaleY) * 0.8f) * AspectRatioZ;
//
//	//UE_LOG(LogTemp, Log, TEXT("GridSize: %f"), OriginalSize.X);
//	//UE_LOG(LogTemp, Log, TEXT("X: %f, Y: %f, Z: %f"), DefaultScaleX, DefaultScaleY, DefaultScaleZ);
//	SetActorScale3D(FVector(DefaultScaleX * 0.1f, DefaultScaleY * 0.1f, DefaultScaleZ * 0.1f));
//}

void ABuilding_GatheringResource::SetNiagaraRange(float Range)
{
	//UE_LOG(LogTemp, Log, TEXT("jjjjjjjjj"));
	NiagaraComponent_Range->SetVariableFloat(TEXT("User.Radius"), Range);
}


void ABuilding_GatheringResource::ChangeRangeCrystal()
{
	ClearCrystalRange();
	CurCrystalArr.Empty();
	CurCrystalArr = ChangeRangeCrystalMat();
}

TArray<class ABuilding_Crystal*> ABuilding_GatheringResource::ChangeRangeCrystalMat()
{
	TArray<class ABuilding_Crystal*> CrystalArr;

	for (FIntPoint ResourcePoint : GridActor->SpawnResourceComponent->Occupied)
	{
		ABuilding_Crystal* Crystal = Cast<ABuilding_Crystal>(GridActor->GridTileArr[ResourcePoint.X].GridTileColumn[ResourcePoint.Y]->ObjectInfo.ObjectActor);
		if (Crystal != nullptr)
		{
			if (this->GetDistanceTo(Crystal) <= GatheringRange)
			{
				CrystalArr.Add(Crystal);
				Crystal->SetGatheringMat(true);
			}
		}
	}

	return CrystalArr;
}

TArray<class ABuilding_Crystal*> ABuilding_GatheringResource::GetRangeCrystal()
{
	TArray<class ABuilding_Crystal*> CrystalArr;

	for (FIntPoint ResourcePoint : GridActor->SpawnResourceComponent->Occupied)
	{
		ABuilding_Crystal* Crystal = Cast<ABuilding_Crystal>(GridActor->GridTileArr[ResourcePoint.X].GridTileColumn[ResourcePoint.Y]->ObjectInfo.ObjectActor);
		if (Crystal != nullptr)
		{
			if (this->GetDistanceTo(Crystal) <= GatheringRange)
			{
				CrystalArr.Add(Crystal);
			}
		}
	}

	return CrystalArr;
}

void ABuilding_GatheringResource::ClearCrystalRange()
{
	for (ABuilding_Crystal* Crystal : CurCrystalArr)
	{
		Crystal->SetGatheringMat(false);
	}
}