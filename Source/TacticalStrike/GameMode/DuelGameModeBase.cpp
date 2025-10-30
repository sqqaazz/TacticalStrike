// Fill out your copyright notice in the Description page of Project Settings.


#include "DuelGameModeBase.h"
#include "Characters/PlayerDuelDefaultUnit.h"
#include "Controllers/DuelPlayerController.h"

ADuelGameModeBase::ADuelGameModeBase()
{
	DefaultPawnClass = APlayerDuelDefaultUnit::StaticClass();
	PlayerControllerClass = ADuelPlayerController::StaticClass();
}
