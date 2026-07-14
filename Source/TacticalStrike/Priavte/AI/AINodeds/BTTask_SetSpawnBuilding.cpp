// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_SetSpawnBuilding.h"
#include "AI/AIController/CommanderAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/BuildingClickableComponent.h"
#include "Objects/GridActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/GridTileActor.h"

UBTTask_SetSpawnBuilding::UBTTask_SetSpawnBuilding()
{
	NodeName = TEXT("CommandAI_SetSpawnBuilding");
}


EBTNodeResult::Type UBTTask_SetSpawnBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));

	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());

	int8 AIHaviorSequenceIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::AIHaviorSequenceIndexKey);
	FHaviorStateSequence HaviorStateSequenceQueue = CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex];

	UnitDataInfo = GameInstance->GetUnitTable(static_cast<int32>(HaviorStateSequenceQueue.SpawnObjectType));
	AIEnergyTileArr = GridActor->CheckAIEnegyTile();
	
	ADefaultBuilding* CurSpawnBuilding = nullptr;
	
	int8 CurUnitDataArryNum = 5;

	for (const UGridTileActor* EnergyTile : AIEnergyTileArr)
	{
		if (EnergyTile->ObjectInfo.ObjectType == uint8(UnitDataInfo->ProductionBuilding))
		{
			UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
				(EnergyTile->ObjectInfo.ObjectActor->GetComponentByClass(UBuildingClickableComponent::StaticClass()));

			if (EnergyTile->ObjectInfo.ObjectState == EObjectState::Activated)
			{
				if (BuildingComponent->UnitDataArray.Num() < CurUnitDataArryNum)
				{
					CurSpawnBuilding = Cast<ADefaultBuilding>(EnergyTile->ObjectInfo.ObjectActor);
					CurUnitDataArryNum = BuildingComponent->UnitDataArray.Num();
					continue;
				}
				else
					continue;
			}
			//else if (EnergyTile->ObjectInfo.ObjectState == EObjectState::DeActivated)
			//{
			//	ADefaultBuilding* SpawnBuilding = Cast<ADefaultBuilding>(EnergyTile->ObjectInfo.ObjectActor);
			//	if (SpawnBuilding->ObjectInfo.CurrentBuildTime >= 0)
			//	{
			//		
			//	}
			//}
		}
		//if (EnergyTile->ObjectInfo.ObjectState == EObjectState::Activated && EnergyTile->ObjectInfo.ObjectType == uint8(UnitDataInfo->ProductionBuilding))
		//{
		//	UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
		//		(EnergyTile->ObjectInfo.ObjectActor->GetComponentByClass(UBuildingClickableComponent::StaticClass()));
		//	if (BuildingComponent->UnitDataArray.Num() < 5)
		//	{
		//	}
		//}
	}
	if (CurSpawnBuilding != nullptr)
	{
		CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState = EAIBehaviorState::Waiting;
		CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].SpawnBuilding = CurSpawnBuilding;
	}
	else
	{
		CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState = EAIBehaviorState::Waited_Building;
		CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].SpawnBuilding = nullptr;
	}

	return EBTNodeResult::Succeeded;
}