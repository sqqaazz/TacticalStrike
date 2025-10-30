// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TacticalStrikeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTacticalStrikeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TACTICALSTRIKE_API ITacticalStrikeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/*UFUNCTION()
	ADefaultUnit* CreateUnit(UWorld* World, ADefaultUnit* DefaultUnitClass, UUnitsArray* UnitsInfo, FVector UnitSpawnLocation);*/

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//FVector CheckUnitSpawnScale(UUnitsArray* UnitsInfo);

	UFUNCTION()
	virtual void TestInter() {
		UE_LOG(LogTemp, Log, TEXT("gggggbbbbbbbbbbbbbbbbb9r238423983294"));
	}
};
