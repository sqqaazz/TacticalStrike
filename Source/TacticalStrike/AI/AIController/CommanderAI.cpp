// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CommanderUnit.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/AIBuildingInfoClass.h"
#include "GameMode/TacticalStrikeGameStateBase.h"
#include "Components/SpawnBuildingComponent.h"

const FName ACommanderAI::ResourceKey(TEXT("ResourceKey"));

const FName ACommanderAI::UnitTypeKey(TEXT("UnitTypeKey"));

const FName ACommanderAI::BehaviorWeightKey(TEXT("BehaviorWeightKey"));

const FName ACommanderAI::BattleFrontWeightKey(TEXT("BattleFrontWeightKey"));
const FName ACommanderAI::TimeWeightKey(TEXT("TimeWeightKey"));

const FName ACommanderAI::BuildWeightKey(TEXT("BuildWeightKey"));
const FName ACommanderAI::UnitWeightKey(TEXT("UnitWeightKey"));
const FName ACommanderAI::WaitWeightKey(TEXT("WaitWeightKey"));
const FName ACommanderAI::ResourceWeightKey(TEXT("ResourceWeightKey"));

//const FName ACommanderAI::AIBuildingInfo(TEXT("AIBuildingInfo"));

//Building 가중치
const FName ACommanderAI::UnitBuildingWeightKey(TEXT("UnitBuildingWeightKey"));
const FName ACommanderAI::ResourceBuildingWeightKey(TEXT("ResourceBuildingWeightKey"));
const FName ACommanderAI::BuildingTypeKey(TEXT("BuildingTypeKey"));

//Upgrade 가중치
const FName ACommanderAI::UpgradeTypeKey(TEXT("UpgradeTypeKey"));

ACommanderAI::ACommanderAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Blueprints/AI/BB_CommanderAI.BB_CommanderAI'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Blueprints/AI/BT_CommanderAI.BT_CommanderAI'"));
	if (BBObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	SpawnBuildingComponent = CreateDefaultSubobject<USpawnBuildingComponent>(TEXT("AI_SpawnBuildingComponent"));
	bBehaviorTreeStarted = false;
}

void ACommanderAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GameStateBase = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	if (GameStateBase != nullptr)
	{
		GameStateBase->AITurnStartDelegate.AddDynamic(this, &ACommanderAI::StartAITurn);
	}

	//GetBlackboardComponent()->SetValueAsFloat(BehaviorWeightKey, 0);
	//GetBlackboardComponent()->SetValueAsFloat(BuildWeightKey, 0.0f);
	//GetBlackboardComponent()->SetValueAsFloat(UnitWeightKey, 0.0f);
	//GetBlackboardComponent()->SetValueAsFloat(ResourceWeightKey, 0.0f);
	
	auto CommanderUnit = Cast<ACommanderUnit>(GetPawn());
	if (CommanderUnit != nullptr)
	{
		CommanderUnit->Tags.Add("CommanderAI");
	}

}

void ACommanderAI::AIBehavior(uint8 ObjectType)
{
	//UE_LOG(LogTemp, Log, TEXT("ObjectType: %d"), ObjectType);

	if (ObjectType < 210 && ObjectType > 100)
		AIBuildingSpawnDelegate.Broadcast(ObjectType);
	else if (ObjectType >= 210)
		AIResearchDelegate.Broadcast(ObjectType);
}

void ACommanderAI::StartAITurn()
{
	//UE_LOG(LogTemp, Log, TEXT("StartAITurn"));
	if (!bBehaviorTreeStarted)
	{
		UBlackboardComponent* BlackboardComp = Blackboard.Get();

		if (UseBlackboard(BBAsset, BlackboardComp))
			RunBehaviorTree(BTAsset);
		this->Blackboard = BlackboardComp;

		GetBlackboardComponent()->SetValueAsFloat(BuildWeightKey, 0.5f);
		GetBlackboardComponent()->SetValueAsFloat(UnitWeightKey, 0.5f);
		GetBlackboardComponent()->SetValueAsFloat(ResourceWeightKey, 0.5f);
		GetBlackboardComponent()->SetValueAsInt(ResourceKey, 1000);
		GetBlackboardComponent()->SetValueAsInt(UpgradeTypeKey, 221);

		bBehaviorTreeStarted = true;
	}
	else
	{

		BrainComponent->RestartLogic();
	}
}

//void ACommanderAI::SetBuildingArr(ADefaultBuilding* DefaultBuilding)
//{
//	FAIBuildingInfo AIBuildingInfoStr;
//	AIBuildingInfoStr.DefaultBuilding = DefaultBuilding;
//	UAIBuildingInfoClass* AIBuildingInfoClass = Cast<UAIBuildingInfoClass>(GetBlackboardComponent()->GetValueAsObject(ACommanderAI::AIBuildingInfo));
//	if (AIBuildingInfoClass != nullptr)
//	{
//		AIBuildingInfoClass->AIBuildingInfo.Add(AIBuildingInfoStr);
//		UObject* SetAIBuildingInfoClass = Cast<UObject>(AIBuildingInfoClass);
//		if (SetAIBuildingInfoClass != nullptr)
//			GetBlackboardComponent()->SetValueAsObject(ACommanderAI::AIBuildingInfo, SetAIBuildingInfoClass);
//	}	
//}