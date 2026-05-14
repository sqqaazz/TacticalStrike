// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Objects/GridActor.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "TeamMainAI.generated.h"

USTRUCT(BlueprintType)
struct FSightEnemyStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint EnemyPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FObjectInfo EnemyInfo;
};

UCLASS()
class TACTICALSTRIKE_API ATeamMainAI : public AAIController
{
	GENERATED_BODY()


public:
	ATeamMainAI();

	void InitializeController();

	static const FName OwnerCommanderAIKey;
	static const FName TeamMainAI_bTriggerActivatedKey;
	static const FName TeamMainAI_bSightTriggerActivatedKey;
	static const FName TeamMainAI_TeamUnitIndexKey;
	//static const FName UnitActionTriggerKey;

	TArray<TArray<class AGridTileActor*>> GridTileArr;
	AGridActor* GridActor;

	//TArray<FSightEnemyStruct> SightEnemyArr;
	UPROPERTY()
	TArray<ADefaultUnit*> SightEnemyArr;
	UPROPERTY()
	TArray<ADefaultUnit*> TeamUnitArr;

	void GetGridField();
	void SetTempGridField(TArray<TArray<class AGridTileActor*>> GridTileArr_Temp);

	FObjectInfo ObjectInfo;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;
	
private:
	bool bBehaviorTreeStarted;

	UFUNCTION()
	void StartAction();
};
