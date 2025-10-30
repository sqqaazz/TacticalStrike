// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetAIResource.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Objects/Buildings/Building_Crystal.h"
#include "AI/AIController/CommanderAI.h"

UBTTask_SetAIResource::UBTTask_SetAIResource()
{
	NodeName = TEXT("SetAIResource");
}

EBTNodeResult::Type UBTTask_SetAIResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuilding_Crystal::StaticClass(), CrystalArray);

	uint8 GettingResourceAmount = 0;

	if (CrystalArray.Num() != 0)
	{
		for (uint8 i = 0; i < CrystalArray.Num(); i++)
		{
			if (CrystalArray[i]->ActorHasTag("RedTeamBuildings"))
				GettingResourceAmount += 10;
		}
		GettingResourceAmount += 30;
	}
	else
		GettingResourceAmount = 30;

	uint32 CurrentResourceAmount = OwnerComp.GetBlackboardComponent()->GetValueAsInt(ACommanderAI::ResourceKey);
	uint32 NewResourceAmount = CurrentResourceAmount + GettingResourceAmount;
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(ACommanderAI::ResourceKey, NewResourceAmount);
	//UE_LOG(LogTemp, Log, TEXT("%d"), NewResourceAmount);
	return EBTNodeResult::Succeeded;

}