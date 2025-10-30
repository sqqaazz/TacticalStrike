// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnBuilding.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
//#include "AIBuildingInfoClass.h"

UBTTask_SpawnBuilding::UBTTask_SpawnBuilding()
{
	NodeName = TEXT("SpawnBuilding");
}

EBTNodeResult::Type UBTTask_SpawnBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//AIBuildingInfoClass = Cast<UAIBuildingInfoClass>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACommanderAI::AIBuildingInfo));
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		uint8 BuildingType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::BuildingTypeKey);
		int32 CurrentResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);

		if (BuildingType == 0)
			return EBTNodeResult::Succeeded;

		if (GameInstance != nullptr)
			BuildingDataTable = GameInstance->GetBuildingTable(BuildingType);

		if (CurrentResource > BuildingDataTable->Cost)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, CurrentResource - BuildingDataTable->Cost);
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BuildWeightKey, 0.0f);

			if (BuildingType < 150)
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitBuildingWeightKey, 0.0f);
			else if (BuildingType >= 150)
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::ResourceBuildingWeightKey, 0.0f);

			ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());
			if (CommanderAI != nullptr)
				CommanderAI->AIBehavior(BuildingType);

			return EBTNodeResult::Succeeded;
		}
		else
		{
			float BuildWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BuildWeightKey);
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BuildWeightKey, BuildWeightKey + 0.1f);
			return EBTNodeResult::Succeeded;
		}

}