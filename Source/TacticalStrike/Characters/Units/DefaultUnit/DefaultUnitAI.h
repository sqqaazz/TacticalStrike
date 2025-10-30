// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/GridTileActor.h"
#include "DefaultUnitAI.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API ADefaultUnitAI : public AAIController
{
	GENERATED_BODY()
public:
	ADefaultUnitAI();

	static const FName SpawnPosKey;
	static const FName MovingPosKey;
	static const FName TargetKey;
	static const FName DistanceKey;

	static const FName MovingObjectPosKey;

	//static const FName GridFieldKey;

	static const FName MainTeamAIKey;
	static const FName UnitActionTriggerKey;
	static const FName DefaultUnitAI_bSightTriggerActivatedKey;

	static const FName ActionCountKey;
	static const FName InPlace_bIsTargetInRange;
	static const FName Move_bIsTargetInRange;

	void StopAI();

	UPROPERTY()
	class AGridActor* GridActor;

	TArray<TArray<AGridTileActor*>> GridTileArr_Temp;

	void GetGridField();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;

private:
	UPROPERTY()
	TArray<AActor*> TampleArr;
};
