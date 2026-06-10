// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "TacticalStrikeGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWorldCommanderTimer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWorldUnitSpawnTrigger);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerTurnStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerTurnStartAfterDelegate);

DECLARE_MULTICAST_DELEGATE(FPlayerCombatAITurnEndDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAITurnStartDelegate);

UCLASS()
class TACTICALSTRIKE_API ATacticalStrikeGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ATacticalStrikeGameStateBase();
	
	int32 Turn;

	int32 CooldownTime;

	//void StartTimer();
	//void AdvanceTimer();
	FTimerHandle CountdownTimerHandle;

	FWorldCommanderTimer WorldCommanderTimer;
	FWorldUnitSpawnTrigger WorldUnitSpawnTrigger;

	FPlayerTurnStartDelegate PlayerTurnStartDelegate;
	FPlayerTurnStartAfterDelegate PlayerTurnStartAfterDelegate;

	FPlayerCombatAITurnEndDelegate PlayerCombatAITurnEndDelegate;

	FAITurnStartDelegate AITurnStartDelegate;

	void PlayerTurnStart();
	void PlayerTurnStart_EndTimer();
	void PlayerCombatAITurnEnd(EObjectOwner ObjectOwner);
	void AITurnStart();
protected:
	/*virtual void InProgress() override;*/
};
