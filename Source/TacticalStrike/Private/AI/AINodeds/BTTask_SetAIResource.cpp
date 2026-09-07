// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_SetAIResource.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Objects/Buildings/Building_Crystal.h"
#include "AI/AIController/CommanderAI.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Objects/Buildings/Building_GatheringResource.h"

UBTTask_SetAIResource::UBTTask_SetAIResource()
{
	NodeName = TEXT("SetAIResource");
}

EBTNodeResult::Type UBTTask_SetAIResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuilding_Crystal::StaticClass(), CrystalArray);

	//uint8 GettingResourceAmount = 0;

	//if (CrystalArray.Num() != 0)
	//{
	//	for (uint8 i = 0; i < CrystalArray.Num(); i++)
	//	{
	//		if (CrystalArray[i]->ActorHasTag("RedTeamBuildings"))
	//			GettingResourceAmount += 10;
	//	}
	//	GettingResourceAmount += 30;
	//}
	//else
	//	GettingResourceAmount = 30;

	TSet<ABuilding_Crystal*> GatheringCrystalArr;

	for (const TWeakObjectPtr<ADefaultBuilding> Building : CommanderAI->AIBuildingsArr)
	{
		if (Building->ObjectInfo.ObjectType == static_cast<uint8>(ESpawnObject::ResourceGathering) &&
			Building->ObjectInfo.ObjectState == EObjectState::Activated)
		{
			ABuilding_GatheringResource* ResourceGathering = Cast<ABuilding_GatheringResource>(Building);
			if (ResourceGathering != nullptr)
			{
				TArray<ABuilding_Crystal*> CrystalArr = ResourceGathering->GetRangeCrystal();

				for (ABuilding_Crystal* Crystal : CrystalArr)
				{
					GatheringCrystalArr.Add(Crystal);
				}
			}
		}
	}

	uint32 CurrentResourceAmount = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
	uint32 NewResourceAmount = CurrentResourceAmount + (GatheringCrystalArr.Num() * 5);
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, NewResourceAmount);
	//UE_LOG(LogTemp, Log, TEXT("%d"), CurrentResourceAmount + 30);
	return EBTNodeResult::Succeeded;

}