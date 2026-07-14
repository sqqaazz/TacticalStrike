// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitsArray.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UUnitsArray : public UObject
{
	GENERATED_BODY()

public:
	uint8 UnitType;
	uint8 UnitCount;
};
