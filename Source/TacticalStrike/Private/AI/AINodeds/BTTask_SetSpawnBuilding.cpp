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
	//AIEnergyTileArr = GridActor->CheckAIEnegyTile();
	
	if (HaviorStateSequenceQueue.IsHaviorChecked == true)
		return EBTNodeResult::Succeeded;
	

	if (HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Failed_Lack_Resource)
		return EBTNodeResult::Succeeded;
	
	

	ADefaultBuilding* CurSpawnBuilding = nullptr;
	
	int32 CurUnitDataArrayNum = 1000;

	for (const TWeakObjectPtr<ADefaultBuilding> Building : CommanderAI->AIBuildingsArr)
	{
		if (Building->ObjectInfo.ObjectType == uint8(UnitDataInfo->ProductionBuilding))
		{
			UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
				(Building->ObjectInfo.ObjectActor->GetComponentByClass(UBuildingClickableComponent::StaticClass()));

			if (Building->ObjectInfo.ObjectState == EObjectState::DeActivated)
			{
				int32 DeActivatedArrayNum = CurUnitDataArrayNum - Building->ObjectInfo.CurrentBuildTime;

				if (DeActivatedArrayNum < CurUnitDataArrayNum)
				{
					CurSpawnBuilding = Cast<ADefaultBuilding>(Building->ObjectInfo.ObjectActor);
					CurUnitDataArrayNum = DeActivatedArrayNum;
					continue;
				}
				else
					continue;
			}
			else if (Building->ObjectInfo.ObjectState == EObjectState::Activated)
			{
				if (BuildingComponent->UnitDataArray.Num() < CurUnitDataArrayNum && BuildingComponent->UnitDataArray.Num() < 5)
				{
					CurSpawnBuilding = Cast<ADefaultBuilding>(Building->ObjectInfo.ObjectActor);
					CurUnitDataArrayNum = BuildingComponent->UnitDataArray.Num();
					continue;
				}
				else
					continue;
			}


			//if (Building->ObjectInfo.ObjectState == EObjectState::Activated)
			//{
			//	if (BuildingComponent->UnitDataArray.Num() < CurUnitDataArryNum)
			//	{
			//		CurSpawnBuilding = Cast<ADefaultBuilding>(Building->ObjectInfo.ObjectActor);
			//		CurUnitDataArryNum = BuildingComponent->UnitDataArray.Num();
			//		continue;
			//	}
			//	else
			//		continue;
			//}
		}
	}


	//for (const UGridTileActor* EnergyTile : AIEnergyTileArr)
	//{
	//	if (EnergyTile->ObjectInfo.ObjectType == uint8(UnitDataInfo->ProductionBuilding))
	//	{
	//		UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
	//			(EnergyTile->ObjectInfo.ObjectActor->GetComponentByClass(UBuildingClickableComponent::StaticClass()));

	//		if (EnergyTile->ObjectInfo.ObjectState == EObjectState::Activated)
	//		{
	//			if (BuildingComponent->UnitDataArray.Num() < CurUnitDataArryNum)
	//			{
	//				CurSpawnBuilding = Cast<ADefaultBuilding>(EnergyTile->ObjectInfo.ObjectActor);
	//				CurUnitDataArryNum = BuildingComponent->UnitDataArray.Num();
	//				continue;
	//			}
	//			else
	//				continue;
	//		}
	//		//else if (EnergyTile->ObjectInfo.ObjectState == EObjectState::DeActivated)
	//		//{
	//		//	ADefaultBuilding* SpawnBuilding = Cast<ADefaultBuilding>(EnergyTile->ObjectInfo.ObjectActor);
	//		//	if (SpawnBuilding->ObjectInfo.CurrentBuildTime >= 0)
	//		//	{
	//		//		
	//		//	}
	//		//}
	//	}
	//	//if (EnergyTile->ObjectInfo.ObjectState == EObjectState::Activated && EnergyTile->ObjectInfo.ObjectType == uint8(UnitDataInfo->ProductionBuilding))
	//	//{
	//	//	UBuildingClickableComponent* BuildingComponent = Cast<UBuildingClickableComponent>
	//	//		(EnergyTile->ObjectInfo.ObjectActor->GetComponentByClass(UBuildingClickableComponent::StaticClass()));
	//	//	if (BuildingComponent->UnitDataArray.Num() < 5)
	//	//	{
	//	//	}
	//	//}
	//}

	//세팅된 유닛을 스폰시킬 건물 중 대기열이 가장 짧은 건물을 찾아 활성 상태일 경우 세팅, 찾지 못하였을 경우 명령 상태를 '스폰 건물 대기'로 변경

	if (HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Waiting_Building)
	{
		if (CurSpawnBuilding != nullptr)
		{
			CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState = EAIBehaviorState::Waiting;
			CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].SpawnBuilding = CurSpawnBuilding;
		}
		else
		{
			CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].IsHaviorChecked = true;
			//CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].SpawnBuilding = nullptr;
		}
	}
	else if (HaviorStateSequenceQueue.AIHaviorState == EAIBehaviorState::Waiting)
	{
		if (CurSpawnBuilding != nullptr)
		{
			CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].SpawnBuilding = CurSpawnBuilding;
		}
		else
		{
			CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].AIHaviorState = EAIBehaviorState::Failed_Lack_Building;
			//CommanderAI->HaviorStateSequenceQueue[AIHaviorSequenceIndex].SpawnBuilding = nullptr;
		}
	}

	return EBTNodeResult::Succeeded;
}