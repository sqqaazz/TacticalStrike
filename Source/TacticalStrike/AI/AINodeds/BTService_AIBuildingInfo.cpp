// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AIBuildingInfo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#//include "AIBuildingInfoClass.h"


UBTService_AIBuildingInfo::UBTService_AIBuildingInfo()
{
	NodeName = TEXT("AIBuildingInfo");
	Interval = 0.3f;
}

void UBTService_AIBuildingInfo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//UAIBuildingInfoClass* AIBuildingInfoClass;
	//AIBuildingInfoClass = Cast<UAIBuildingInfoClass>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACommanderAI::AIBuildingInfo));
	//GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//if (AIBuildingInfoClass != nullptr && AIBuildingInfoClass->AIBuildingInfo.Num() > 0)
	//{
	//	for (uint8 i = 0; i < AIBuildingInfoClass->AIBuildingInfo.Num(); i++)
	//	{
	//		if (AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo.Num() > 0)
	//		{
	//			AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo[0].CurrentProgressTime += DeltaSeconds;
	//			UE_LOG(LogTemp, Log, TEXT("Current: %f, BuildTime: %d"), AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo[0].CurrentProgressTime,
	//				AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo[0].UnitDataTable->BuildTime);
	//			if (AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo[0].CurrentProgressTime >
	//				AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo[0].UnitDataTable->BuildTime)
	//			{
	//				//OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::UnitWeightKey, 0.0f);
	//				/*AIBehaviorDelegate.Broadcast(AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo[0].UnitDataTable->UnitType);*/

	//				ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner());
	//				if (CommanderAI != nullptr)
	//					CommanderAI->AIBehavior(AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo[0].UnitDataTable->UnitType);

	//				AIBuildingInfoClass->AIBuildingInfo[i].WaitingUnitInfo.RemoveAt(0);
	//			}
	//		}
	//		else if (AIBuildingInfoClass->AIBuildingInfo[i].ResearchWaitingInfo.Num() > 0)
	//		{
	//			AIBuildingInfoClass->AIBuildingInfo[i].ResearchWaitingInfo[0].CurrentProgressTime += DeltaSeconds;
	//		}
	//	}
	//}
	//UObject* AIBuildingInfoObject = Cast<UObject>(AIBuildingInfoClass);
	//OwnerComp.GetBlackboardComponent()->SetValueAsObject(ACommanderAI::AIBuildingInfo, AIBuildingInfoObject);

}