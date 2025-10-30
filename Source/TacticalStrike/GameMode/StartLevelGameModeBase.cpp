// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelGameModeBase.h"
#include "Controllers/MainMenuController.h"
#include "Characters/MainMenuUnit.h"
AStartLevelGameModeBase::AStartLevelGameModeBase()
{
	DefaultPawnClass = AMainMenuUnit::StaticClass();
	PlayerControllerClass = AMainMenuController::StaticClass();
	//GameStateClass = ATacticalStrikeGameStateBase::StaticClass();
}