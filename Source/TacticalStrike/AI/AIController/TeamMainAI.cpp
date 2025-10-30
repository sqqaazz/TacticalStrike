// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIController/TeamMainAI.h"
#include "Objects/GridActor.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ATeamMainAI::OwnerCommanderAIKey(TEXT("OwnerCommanderAIKey"));
const FName ATeamMainAI::TeamMainAI_bTriggerActivatedKey(TEXT("TeamMainAI_bTriggerActivatedKey"));
const FName ATeamMainAI::TeamMainAI_bSightTriggerActivatedKey(TEXT("TeamMainAI_bSightTriggerActivatedKey"));

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
	StartAction();
}

void ATeamMainAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ATeamMainAI::StartAction()
{
		if (!bBehaviorTreeStarted)
	{
		UBlackboardComponent* BlackboardComp = Blackboard.Get();

		if (UseBlackboard(BBAsset, BlackboardComp))
			RunBehaviorTree(BTAsset);
		this->Blackboard = BlackboardComp;
		GetBlackboardComponent()->SetValueAsBool(TeamMainAI_bTriggerActivatedKey, true);
		GetBlackboardComponent()->SetValueAsBool(TeamMainAI_bSightTriggerActivatedKey, true);
		bBehaviorTreeStarted = true;
	}
	else
	{

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

