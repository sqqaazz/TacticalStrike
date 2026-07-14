// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TacticalStrikeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API ATacticalStrikeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATacticalStrikeGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	virtual void StartPlay() override;
};
