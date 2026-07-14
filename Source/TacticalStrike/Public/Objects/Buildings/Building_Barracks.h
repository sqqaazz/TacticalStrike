// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "DefaultBuilding.h"
//#include "BuildingClickableComponent.h"
#include "Building_Barracks.generated.h"

UCLASS()
class TACTICALSTRIKE_API ABuilding_Barracks : public ADefaultBuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding_Barracks();

	void SetEnableMat() override;
	void SetDisableMat() override;
	void SetBasicMat() override;

	void GetBuildingMaterial();
	UMaterialInterface* LeftDoorMat;
	UMaterialInterface* RightDoorMat;

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

private:

};
