// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticalStrikeInterface.h"
//#include "DefaultUnit.h"
//#include "RifleMan.h"
//#include "SwordMan.h"
//#include "Mutant.h"
//#include "UnitsArray.h"

// Add default functionality here for any ITacticalStrikeInterface functions that are not pure virtual.

//ADefaultUnit* ITacticalStrikeInterface::CreateUnit(UWorld* World, ADefaultUnit* DefaultUnitClass, UUnitsArray* UnitsInfo, FVector UnitSpawnLocation)
//{
//	ADefaultUnit* DefaultUnit = nullptr;
//    if (UnitsInfo && World)
//    {
//        if (UnitsInfo->UnitType == 1)
//        {
//            DefaultUnit = World->SpawnActor<ADefaultUnit>(DefaultUnitClass, UnitSpawnLocation, FRotator::ZeroRotator);
//        }
//        else if (UnitsInfo->UnitType == 2)
//        {
//            DefaultUnit = World->SpawnActor<ASwordMan>(DefaultUnitClass, UnitSpawnLocation, FRotator::ZeroRotator);
//        }
//        else if (UnitsInfo->UnitType == 3)
//        {
//            DefaultUnit = World->SpawnActor<AMutant>(DefaultUnitClass, UnitSpawnLocation, FRotator::ZeroRotator);
//        }
//    }
//    return DefaultUnit;
//}

//FVector ITacticalStrikeInterface::CheckUnitSpawnScale(UUnitsArray* UnitsInfo)
//{
//	UE_LOG(LogTemp, Log, TEXT("nnnnnnnnbbbbdfgzzrzzzzfg"));
//	return FVector(50.0f, 50.0f, 50.0f);
//}