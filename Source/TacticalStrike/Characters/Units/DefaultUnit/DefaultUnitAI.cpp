// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultUnitAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Tample/DefaultTample.h"
#include "Objects/GridActor.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"

const FName ADefaultUnitAI::SpawnPosKey(TEXT("DefaultUnitSpawnPos"));
const FName ADefaultUnitAI::MovingPosKey(TEXT("DefaultUnitMovingPos"));
const FName ADefaultUnitAI::TargetKey(TEXT("DefaultUnitTarget"));
const FName ADefaultUnitAI::DistanceKey(TEXT("DefaultUnitDistanceToTarget"));
const FName ADefaultUnitAI::MovingObjectPosKey(TEXT("MovingObjectPosKey"));

//const FName ADefaultUnitAI::GridFieldKey(TEXT("GridFieldKey"));
const FName ADefaultUnitAI::MainTeamAIKey(TEXT("MainTeamAIKey"));
const FName ADefaultUnitAI::UnitActionTriggerKey(TEXT("UnitActionTriggerKey"));
const FName ADefaultUnitAI::DefaultUnitAI_bSightTriggerActivatedKey(TEXT("DefaultUnitAI_bSightTriggerActivatedKey"));

const FName ADefaultUnitAI::ActionCountKey(TEXT("ActionCountKey"));
const FName ADefaultUnitAI::InPlace_bIsTargetInRange(TEXT("InPlace_bIsTargetInRange"));
const FName ADefaultUnitAI::Move_bIsTargetInRange(TEXT("Move_bIsTargetInRange"));

ADefaultUnitAI::ADefaultUnitAI()
{
}

void ADefaultUnitAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultTample::StaticClass(), TampleArr);

	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		
		//ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(GetPawn());
		//if (DefaultUnit != nullptr)
		//{
		//	ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(DefaultUnit->GetController());
		//	if (DefaultUnitAI != nullptr)
		//	{
		//		if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Red)
		//		{
		//			//DefaultUnitAI->GetBlackboardComponent()->SetValueAsObject()
		//		}
		//		if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Blue)
		//		{

		//		}
		//	}
		//}

		//for (int32 i = 0; i < TampleArr.Num(); i++)
		//{
		//	if (GetPawn()->ActorHasTag("BlueTeamUnit") && TampleArr[i]->ActorHasTag("RedTeamTample"))
		//	{
		//		Blackboard->SetValueAsObject(ADefaultUnitAI::MovingObjectPosKey, TampleArr[i]);
		//	}
		//	else if (GetPawn()->ActorHasTag("RedTeamUnit") && TampleArr[i]->ActorHasTag("BlueTeamTample"))
		//	{
		//		Blackboard->SetValueAsObject(ADefaultUnitAI::MovingObjectPosKey, TampleArr[i]);
		//	}
		//}

		/*if (GetPawn()->ActorHasTag("BlueTeamUnit"))
		{
			Blackboard->SetValueAsVector(MovingPosKey, FVector(10000.0f, 3000.0f, 0.0f));
		}
		else if (GetPawn()->ActorHasTag("RedTeamUnit"))
		{
			Blackboard->SetValueAsVector(MovingPosKey, FVector(1800.0f, 3000.0f, 0.0f));
		}
		else
			return;*/

		RunBehaviorTree(BTAsset);

		GetBlackboardComponent()->SetValueAsBool(UnitActionTriggerKey, false);
		GetBlackboardComponent()->SetValueAsBool(DefaultUnitAI_bSightTriggerActivatedKey, false);
		GetBlackboardComponent()->SetValueAsBool(InPlace_bIsTargetInRange, false);
		GetBlackboardComponent()->SetValueAsBool(Move_bIsTargetInRange, false);

		GetBlackboardComponent()->SetValueAsInt(ActionCountKey, 0);
	}
	this->Blackboard = BlackboardComp;
}

void ADefaultUnitAI::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void ADefaultUnitAI::GetGridField()
{
	GridTileArr_Temp = GridActor->GridTileArr;
}