// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DefaultUnitAttack.h"
#include "DefaultUnitAI.h"
#include "DefaultUnit.h"
#include "Objects/GridActor.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AIController/TeamMainAI.h"

UBTTask_DefaultUnitAttack::UBTTask_DefaultUnitAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_DefaultUnitAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));

	ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::MainTeamAIKey));
	ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	ADefaultUnit* UnitTarget = Cast<ADefaultUnit>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::CurTargetKey));

	if (DefaultUnit->Attack >= UnitTarget->CurrentHP)
	{
		TeamMainAI->SightEnemyArr.Remove(UnitTarget);
	}

	DefaultUnit->Attacking();
	IsAttacking = true;

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(ADefaultUnitAI::ActionCountKey, 0);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::InPlace_bIsTargetInRange, false);
	DefaultUnit->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTTask_DefaultUnitAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
