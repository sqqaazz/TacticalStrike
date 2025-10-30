// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ResourceResearch.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "AI/AIController/CommanderAI.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/BuildingClickableComponent.h"

UBTTask_ResourceResearch::UBTTask_ResourceResearch()
{
	NodeName = TEXT("ResourceResearch");
}

EBTNodeResult::Type UBTTask_ResourceResearch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int32 CurrentResource = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
	int UpgradeType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::UpgradeTypeKey);

	if (GameInstance != nullptr)
		UpgradeDataTable = GameInstance->GetUpgradeTable(UpgradeType);

	if (UpgradeDataTable->Cost > CurrentResource)
	{
		float ResourceWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::ResourceWeightKey);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::ResourceWeightKey, ResourceWeightKey + 0.1f);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		TArray<AActor*> BuildingArray;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultBuilding::StaticClass(), BuildingArray);

		for (uint8 i = 0; i < BuildingArray.Num(); i++)
		{
			ADefaultBuilding* SpawnBuilding = Cast<ADefaultBuilding>(BuildingArray[i]);
			if (SpawnBuilding != nullptr && SpawnBuilding->ActorHasTag("RedTeamBuildings")
				&& SpawnBuilding->BuildingType == UpgradeDataTable->ProductionBuilding)
			{
				UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
					(SpawnBuilding->GetComponentByClass(UBuildingClickableComponent::StaticClass()));
				if (BuildingComponent != nullptr)
				{
					if (BuildingComponent->DefaultResearchTime == 0.0f)
					{
						BuildingComponent->GetResearchTime(221);
						int32 NewResource = CurrentResource - UpgradeDataTable->Cost;
						OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, NewResource);
						OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::ResourceWeightKey, 0.0f);
						return EBTNodeResult::Succeeded;
					}
				}

			}
		}

		float ResourceBuildingWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::ResourceBuildingWeightKey);
		float BuildWeightKey = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(ACommanderAI::BuildWeightKey);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::ResourceBuildingWeightKey, ResourceBuildingWeightKey + 0.1f);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BuildWeightKey, BuildWeightKey + 0.1f);
		return EBTNodeResult::Succeeded;
	}


}