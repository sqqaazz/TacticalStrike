// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "CommanderAI.generated.h"

//건물에서 카운트 장소로 유닛 스폰 시 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAICountPlaceSpawnDelegate, FString, Team, uint8, UnitType);
//건물 스폰 시 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIBuildingSpawnDelegate, uint8, BuildingType);
//연구 완료 시 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIResearchDelegate, uint8, ResearchType);
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAIBehaviorDelegate, uint8, ObjectType);

UENUM(BlueprintType)
enum class EAIBehaviorCode : uint8
{
	None = 0 UMETA(DisPlayName = "None"),
	Havior_Idle = 1 UMETA(DisPlayName = "Havior_Idle"),
	Havior_SpawnUnit = 2 UMETA(DisPlayName = "Havior_SpawnUnit"),
	Havior_SpawnBuilding_Unit = 3 UMETA(DisPlayName = "Havior_SpawnBuilding_Unit"),
	Havior_SpawnBuilding_Research = 4 UMETA(DisPlayName = "Havior_SpawnBuilding_Research"),
	Havior_SpawnBuilding_Resource = 5 UMETA(DisPlayName = "Havior_SpawnBuilding_Resource"),
	Havior_SpawnBuilding_Territory = 6 UMETA(DisPlayName = "Havior_SpawnBuilding_Territory"),
	Havior_Research = 7 UMETA(DisPlayName = "Havior_Research"),
	Havior_TurnEnd = 8 UMETA(DisPlayName = "Havior_TurnEnd"),

};


UENUM(BlueprintType)
enum class EAIBehaviorState : uint8
{
	None = 0 UMETA(DisPlayName = "None"),
	Successed = 1 UMETA(DisPlayName = "Successed"),
	Waiting = 2 UMETA(DisPlayName = "Waiting"),
	Failed_Lack_Resource = 3 UMETA(DisPlayName = "Failed_Lack_Resource"),
	Failed_Lack_Building = 4 UMETA(DisPlayName = "Failed_Lack_Building"),
	Failed_Lack_Territory = 5 UMETA(DisPlayName = "Failed_Lack_Territory"),
	Waited_Building = 6 UMETA(DisPlayName = "Waited_Building")
};

USTRUCT(BlueprintType)
struct FHaviorStateSequence
{
	GENERATED_BODY()

	UPROPERTY()
	EAIBehaviorCode HaviorCode;

	UPROPERTY()
	EAIBehaviorState AIHaviorState;

	UPROPERTY()
	int32 HaviorWaitingTurn;

	UPROPERTY()
	ESpawnObject SpawnObjectType;

	UPROPERTY()
	TWeakObjectPtr<ADefaultBuilding> SpawnBuilding;
	
};

UCLASS()
class TACTICALSTRIKE_API ACommanderAI : public AAIController
{
	GENERATED_BODY()
	
public:
	ACommanderAI();

	//보유한 자원
	static const FName ResourceKey;

	//지휘 AI가 본인의 행동 명령을 실행 중인지 판단할 때 
	static const FName bIsAICommandingKey;

	static const FName AIHaviorKey;
	static const FName PreviousAIHaviorStateKey;

	//

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

	UPROPERTY()
	TArray<FHaviorStateSequence> HaviorStateSequenceQueue;

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
