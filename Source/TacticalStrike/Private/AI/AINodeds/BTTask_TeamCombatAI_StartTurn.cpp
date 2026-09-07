// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_TeamCombatAI_StartTurn.h"
#include "GameMode/TacticalStrikeGameStateBase.h"


UBTTask_TeamCombatAI_StartTurn::UBTTask_TeamCombatAI_StartTurn()
{
	NodeName = TEXT("CombatAI_StartTurn");
}

EBTNodeResult::Type UBTTask_TeamCombatAI_StartTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATacticalStrikeGameStateBase* GameStateBase = Cast<ATacticalStrikeGameStateBase>(GetWorld()->GetGameState());
	//ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	if (GameStateBase != nullptr)
	{
		GameStateBase->PlayerTurnStartAfterDelegate.AddDynamic(this, &UBTTask_TeamCombatAI_StartTurn::StartTurn_Player);
		GameStateBase->AITurnStartDelegate.AddDynamic(this, &UBTTask_TeamCombatAI_StartTurn::StartTurn_AI);


		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_TeamCombatAI_StartTurn::StartTurn_Player()
{

}

void UBTTask_TeamCombatAI_StartTurn::StartTurn_AI()
{

}