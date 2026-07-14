// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameMode/TacticalStrikeGameModeBase.h"
#include "Characters/CommanderUnit.h"
#include "Controllers/CommanderController.h"
#include "GameMode/TacticalStrikeGameStateBase.h"

ATacticalStrikeGameModeBase::ATacticalStrikeGameModeBase()
{
	DefaultPawnClass = ACommanderUnit::StaticClass();
	PlayerControllerClass = ACommanderController::StaticClass();
	GameStateClass = ATacticalStrikeGameStateBase::StaticClass();
}

void ATacticalStrikeGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ATacticalStrikeGameModeBase::StartPlay()
{
	Super::StartPlay();

	auto Tactical = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	if (Tactical != nullptr)
	{
		//Tactical->StartTimer();
		Tactical->PlayerTurnStart();
	}
}