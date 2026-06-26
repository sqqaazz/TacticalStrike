// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_SetSpawnBuilding.h"
#include "AI/AIController/CommanderAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Components/BuildingClickableComponent.h"
#include "DataTables/UnitDataTables.h"

UBTTask_SetSpawnBuilding::UBTTask_SetSpawnBuilding()
{
	NodeName = TEXT("CommandAI_SetSpawnBuilding");
}


EBTNodeResult::Type UBTTask_SetSpawnBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));

	return EBTNodeResult::Succeeded;
}