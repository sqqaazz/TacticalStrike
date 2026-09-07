// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Units/DefaultUnit/BTTask_DefaultUnit_GetTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/TeamMainAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/GridActor.h"

UBTTask_DefaultUnit_GetTarget::UBTTask_DefaultUnit_GetTarget()
{
	NodeName = TEXT("DefaultUnit_GetTarget");
}

EBTNodeResult::Type UBTTask_DefaultUnit_GetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::MainTeamAIKey));
	ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	UnitDataInfo = GameInstance->GetUnitTable(static_cast<int32>(DefaultUnit->ObjectInfo.ObjectType));

	TArray<AActor*> SightEnemyArr = TeamMainAI->SightEnemyArr;
	AActor* UnitFinalTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::FinalTargetKey));

	if (UnitFinalTarget == nullptr || TeamMainAI == nullptr || DefaultUnit == nullptr)
		return EBTNodeResult::Failed;
	//UE_LOG(LogTemp, Log, TEXT("vtttttttttccccc"));
	if (SightEnemyArr.IsEmpty())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::CurTargetKey, UnitFinalTarget);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::InPlace_bIsTargetInRange, false);
		return EBTNodeResult::Succeeded;
	}
	float UnitRange = UnitDataInfo->Range;

	for (AActor* SightEnemy : SightEnemyArr)
	{
		if (UnitRange < DefaultUnit->GetDistanceTo(SightEnemy))
			continue;

		if (DefaultUnit->GetDistanceTo(SightEnemy) <= DefaultUnit->GetDistanceTo(UnitFinalTarget))
			UnitFinalTarget = SightEnemy;

		//UE_LOG(LogTemp, Log, TEXT("%f"), DefaultUnit->GetDistanceTo(SightEnemy));

	}
	if (DefaultUnit->GetDistanceTo(UnitFinalTarget) < UnitRange)
	{
		//UE_LOG(LogTemp, Log, TEXT("%f"), DefaultUnit->GetDistanceTo(UnitFinalTarget));
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::InPlace_bIsTargetInRange, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADefaultUnitAI::CurTargetKey, UnitFinalTarget);
	}

	return EBTNodeResult::Succeeded;
}