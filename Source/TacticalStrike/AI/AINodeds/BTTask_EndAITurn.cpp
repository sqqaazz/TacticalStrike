// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_EndAITurn.h"
#include "GameMode/TacticalStrikeGameStateBase.h"
#include "AI/AIController/CommanderAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_EndAITurn::UBTTask_EndAITurn()
{
	NodeName = TEXT("EndAITurn");
}

EBTNodeResult::Type UBTTask_EndAITurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATacticalStrikeGameStateBase* GameStateBase = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	if (GameStateBase != nullptr && CommanderAI != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("EndAITurn"));
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::PreviousAIHaviorStateKey, static_cast<uint8>(EAIBehaviorState::None));
		GameStateBase->PlayerTurnStart();
		CommanderAI->BrainComponent->StopLogic("Turn End");

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}