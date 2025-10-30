// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Building_EnergyRepeater.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API ABuilding_EnergyRepeater : public ADefaultBuilding
{
	GENERATED_BODY()
	
public:
	ABuilding_EnergyRepeater();

protected:
	virtual void BeginPlay() override;
};
