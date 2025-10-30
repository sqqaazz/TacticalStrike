// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticalStrikeGameStateBase.h"

ATacticalStrikeGameStateBase::ATacticalStrikeGameStateBase()
{
	//UE_LOG(LogTemp, Log, TEXT("%f"), GetServerWorldTimeSeconds());
	//CooldownTime = 20;
	//GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATacticalStrikeGameStateBase::AdvanceTimer, 1.0f, true);

	Turn = 0;
}

void ATacticalStrikeGameStateBase::PlayerTurnStart()
{
	Turn++;
	PlayerTurnStartDelegate.Broadcast();
	PlayerTurnStartAfterDelegate.Broadcast();
}

void ATacticalStrikeGameStateBase::AITurnStart()
{
	AITurnStartDelegate.Broadcast();
}

//void ATacticalStrikeGameStateBase::StartTimer()
//{
//	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATacticalStrikeGameStateBase::AdvanceTimer, 1.0f, true);
//}
//
//void ATacticalStrikeGameStateBase::AdvanceTimer()
//{
//	--CooldownTime;
//	WorldCommanderTimer.Broadcast();
//	//UE_LOG(LogTemp, Log, TEXT("World: %f"), GetServerWorldTimeSeconds());
//	//UE_LOG(LogTemp, Log, TEXT("Time: %d"), CooldownTime);
//
//	if (CooldownTime < 1)
//	{
//		CooldownTime = 20;
//		WorldUnitSpawnTrigger.Broadcast();
//		//GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
//	}
//}



