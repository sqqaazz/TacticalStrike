// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/GridTileActor.h"
#include "DefaultUnitAI.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnitTurnEndDelegate);

UCLASS()
class TACTICALSTRIKE_API ADefaultUnitAI : public AAIController
{
	GENERATED_BODY()
public:
	ADefaultUnitAI();

	static const FName SpawnPosKey;
	static const FName MovingPosKey;

	//유닛의 최총 타겟을 설정하는 키
	static const FName FinalTargetKey;

	//유닛의 현재 타겟을 설정하는 키
	static const FName CurTargetKey;


	static const FName DistanceKey;

	static const FName MovingObjectPosKey;

	//static const FName GridFieldKey;

	static const FName MainTeamAIKey;
	static const FName UnitActionTriggerKey;

	//유닛의 시야에 있는 적을 찾는 액션의 트리거 키
	static const FName DefaultUnitAI_bSightTriggerActivatedKey;

	static const FName ActionCountKey;

	//현재 위치에서 사거리 내의 타깃이 있는지 여부를 체크하는 키
	static const FName InPlace_bIsTargetInRange;

	static const FName Move_bIsTargetInRange;

	void StopAI();

	UPROPERTY()
	class AGridActor* GridActor;

	//TArray<TArray<AGridTileActor*>> GridTileArr_Temp;

	void GetGridField();

	UPROPERTY()
	int32 LifeTime;

	void StartUnitTurn();
	UFUNCTION()
	void EndUnitTurn();


	FUnitTurnEndDelegate UnitTurnEndDelegate;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;

private:
	UPROPERTY()
	TArray<AActor*> TempleArr;

};
