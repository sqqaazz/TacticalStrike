// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckUnitResource.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"

UBTTask_CheckUnitResource::UBTTask_CheckUnitResource()
{
	NodeName = TEXT("CheckUnitResource");
}

EBTNodeResult::Type UBTTask_CheckUnitResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	uint8 UnitType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::UnitTypeKey);
	int32 CurrentResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);

	//처음으로 돌아가기 위해 성공 반환
	if (UnitType == 0)
		return EBTNodeResult::Succeeded;

	if (GameInstance != nullptr)
		UnitDataTable = GameInstance->GetUnitTable(UnitType);

	if (UnitDataTable->Cost > CurrentResource)
	{
		float UnitWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::UnitWeightKey);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, UnitWeightKey + 0.1f);
		//처음으로 돌아가기 위해 성공 반환
		return EBTNodeResult::Succeeded;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, 0.0f);
		int32 NewResource = CurrentResource - UnitDataTable->Cost;
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, NewResource);
		//다음 노드로 진행하기 위해 실패 반환
		return EBTNodeResult::Failed;
	}
	
}