// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIController/TeamMainAI.h"
#include "Objects/GridActor.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameMode/TacticalStrikeGameStateBase.h"

//TeamMainAI를 소유한 CommanderAI를 나타내는 키
const FName ATeamMainAI::OwnerCommanderAIKey(TEXT("OwnerCommanderAIKey"));

const FName ATeamMainAI::TeamMainAI_bTriggerActivatedKey(TEXT("TeamMainAI_bTriggerActivatedKey"));
const FName ATeamMainAI::TeamMainAI_bSightTriggerActivatedKey(TEXT("TeamMainAI_bSightTriggerActivatedKey"));

//소유한 유닛 배열의 현재 인덱스를 관리하는 키
const FName ATeamMainAI::TeamMainAI_TeamUnitIndexKey(TEXT("TeamMainAI_TeamUnitIndexKey"));;
ATeamMainAI::ATeamMainAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprints/AI/BB_TeamMainAI.BB_TeamMainAI'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprints/AI/BT_TeamMainAI.BT_TeamMainAI'"));
	if (BBObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	bBehaviorTreeStarted = false;

	
}

void ATeamMainAI::InitializeController()
{
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	ATacticalStrikeGameStateBase* GameStateBase = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	if (GameStateBase != nullptr)
	{
		GameStateBase->PlayerTurnStartAfterDelegate.AddDynamic(this, &ATeamMainAI::StartAction);
		GameStateBase->AITurnStartDelegate.AddDynamic(this, &ATeamMainAI::StartAction);
	}
	StartAction();
}

void ATeamMainAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ATacticalStrikeGameStateBase* GameStateBase = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
}

void ATeamMainAI::StartAction()
{
	if (!bBehaviorTreeStarted)
	{
		UBlackboardComponent* BlackboardComp = Blackboard.Get();

		if (UseBlackboard(BBAsset, BlackboardComp))
			RunBehaviorTree(BTAsset);
		this->Blackboard = BlackboardComp;
		GetBlackboardComponent()->SetValueAsBool(ATeamMainAI::TeamMainAI_bTriggerActivatedKey, true);
		GetBlackboardComponent()->SetValueAsBool(ATeamMainAI::TeamMainAI_bSightTriggerActivatedKey, true);

		GetBlackboardComponent()->SetValueAsInt(ATeamMainAI::TeamMainAI_TeamUnitIndexKey, INDEX_NONE);
		//int32 TempUnitKey = GetBlackboardComponent()->GetValueAsInt(ATeamMainAI::TeamMainAI_TeamUnitIndexKey);
		bBehaviorTreeStarted = true;
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("Clear###fffffffff#####"));
		BrainComponent->RestartLogic();
	}
}

void ATeamMainAI::GetGridField()
{
	GridTileArr = GridActor->GridTileArr;
}

void ATeamMainAI::SetTempGridField(TArray<TArray<class AGridTileActor*>> GridTileArr_Temp)
{

}

