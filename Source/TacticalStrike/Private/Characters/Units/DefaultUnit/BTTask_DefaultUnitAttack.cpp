// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Units/DefaultUnit/BTTask_DefaultUnitAttack.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Objects/GridActor.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AIController/TeamMainAI.h"
#include "Objects/Buildings/DefaultBuilding.h"

UBTTask_DefaultUnitAttack::UBTTask_DefaultUnitAttack()
{
	//bNotifyTick = true;
	NodeName = TEXT("DefaultUnit_Attack");
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_DefaultUnitAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	//bCreateNodeInstance = true;
	CurOwnerComp = &OwnerComp;

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));

	ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::MainTeamAIKey));
	ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::CurTargetKey));
	DefaultUnit->OnAttackEnd.AddUniqueDynamic(this, &UBTTask_DefaultUnitAttack::FinishUnithaviorTask);

	if (Cast<ADefaultUnit>(Target) != nullptr)
	{
		ADefaultUnit* UnitTarget = Cast<ADefaultUnit>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::CurTargetKey));

		if (DefaultUnit->Attack >= UnitTarget->CurrentHP)
		{
			TeamMainAI->SightEnemyArr.Remove(UnitTarget);

			ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(UnitTarget->GetController());
			ATeamMainAI* EnemyTeamMainAI = Cast<ATeamMainAI>(DefaultUnitAI->GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::MainTeamAIKey));
			if (EnemyTeamMainAI != nullptr)
				EnemyTeamMainAI->TeamUnitArr.Remove(UnitTarget);
			
		}
	}
	else if (Cast<ADefaultBuilding>(Target) != nullptr)
	{
		ADefaultBuilding* BuildingTarget = Cast<ADefaultBuilding>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::CurTargetKey));
		if (DefaultUnit->Attack >= BuildingTarget->CurrentHP)
		{
			TeamMainAI->SightEnemyArr.Remove(BuildingTarget);
		}

	}

	DefaultUnit->Attacking(Target);
	//IsAttacking = true;
	//OwnerComp.GetBlackboardComponent()->SetValueAsInt(ADefaultUnitAI::ActionCountKey, 0);
	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::InPlace_bIsTargetInRange, false);
	//DefaultUnit->OnAttackEnd.AddLambda([this]() -> void {
	//	IsAttacking = false;

	//	});

	return EBTNodeResult::InProgress;
}


void UBTTask_DefaultUnitAttack::FinishUnithaviorTask()
{
	CurOwnerComp->GetBlackboardComponent()->SetValueAsInt(ADefaultUnitAI::ActionCountKey, 0);
	CurOwnerComp->GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::InPlace_bIsTargetInRange, false);

	FinishLatentTask(*CurOwnerComp, EBTNodeResult::Succeeded);
}

//void UBTTask_DefaultUnitAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//	if (!IsAttacking)
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//	}
//}
