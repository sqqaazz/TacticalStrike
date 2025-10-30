// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TacticalStrikeInterface.h"
#include "InterfaceImplementer.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UInterfaceImplementer : public UObject, public ITacticalStrikeInterface
{
	GENERATED_BODY()
	
public:
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//FVector CheckUnitSpawnScale(UUnitsArray* UnitsInfo);
	//FVector CheckUnitSpawnScale_Implementation(UUnitsArray* UnitsInfo) override;

	/*virtual void TestInter() override;*/
};
