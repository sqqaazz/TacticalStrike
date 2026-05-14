// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CommanderAI.generated.h"

//건물에서 카운트 장소로 유닛 스폰 시 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAICountPlaceSpawnDelegate, FString, Team, uint8, UnitType);
//건물 스폰 시 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIBuildingSpawnDelegate, uint8, BuildingType);
//연구 완료 시 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIResearchDelegate, uint8, ResearchType);
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIBehaviorDelegate, uint8, ObjectType);


UCLASS()
class TACTICALSTRIKE_API ACommanderAI : public AAIController
{
	GENERATED_BODY()
	
public:
	ACommanderAI();

	//보유한 자원
	static const FName ResourceKey;

	static const FName BehaviorWeightKey;
	static const FName TotalWeightKey;
	static const FName BattleFrontWeightKey;
	static const FName TimeWeightKey;

	static const FName BuildWeightKey;
	static const FName UnitWeightKey;
	static const FName WaitWeightKey;
	static const FName ResourceWeightKey;
	static const FName TechWeightKey;

	//Units 가중치
	static const FName UnitTypeKey;

	//Building 가중치
	static const FName UnitBuildingWeightKey;
	static const FName ResourceBuildingWeightKey;
	static const FName BuildingTypeKey;
	//BuildingInfo
	//static const FName AIBuildingInfo;

	//Upgrade 가중치
	static const FName UpgradeTypeKey;


	UPROPERTY(BlueprintAssignable)
	FAICountPlaceSpawnDelegate AICountPlaceSpawnDelegate;
	UPROPERTY(BlueprintAssignable)
	FAIBuildingSpawnDelegate AIBuildingSpawnDelegate;
	UPROPERTY(BlueprintAssignable)
	FAIResearchDelegate AIResearchDelegate;

	void AIBehavior(uint8 ObjectType);
	//void AIBuildingBehavior(uint8 BuildingType);

	void SetBuildingArr(class ADefaultBuilding* DefaultBuilding);

	UFUNCTION()
	void StartAITurn();

	UPROPERTY()
	class USpawnBuildingComponent* SpawnBuildingComponent;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;

private:
	bool bBehaviorTreeStarted;

	UPROPERTY()
	class ATacticalStrikeGameStateBase* GameStateBase;
};
