// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultUnitAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Tample/DefaultTample.h"
#include "Objects/Buildings/DefaultBuilding.h"
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

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultTample::StaticClass(), TempleArr);

	GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		
		for (auto Temple : TempleArr)
		{
			//ADefaultTample* DefaultTemple = Cast<ADefaultTample>(Temple);
			ADefaultBuilding* DefaultBuilding = Cast<ADefaultBuilding>(Temple);
			ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(InPawn);
			if (DefaultBuilding != nullptr)
			{
				if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Blue && DefaultBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Red)
				{
					Blackboard->SetValueAsObject(ADefaultUnitAI::TargetKey, DefaultBuilding);
				}
				else if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Red && DefaultBuilding->ObjectInfo.ObjectOwner == EObjectOwner::Blue)
				{
					Blackboard->SetValueAsObject(ADefaultUnitAI::TargetKey, DefaultBuilding);
				}
			}
		}

		//for (int32 i = 0; i < TempleArr.Num(); i++)
		//{
		//	ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(GetOwner());
		//	if (DefaultUnit != nullptr)
		//	{
		//		if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Red)
		//		{

		//		}
		//	}

		//	if (GetPawn()->ActorHasTag("BlueTeamUnit") && TempleArr[i]->ActorHasTag("RedTeamTample"))
		//	{
		//		Blackboard->SetValueAsObject(ADefaultUnitAI::MovingObjectPosKey, TempleArr[i]);
		//	}
		//	else if (GetPawn()->ActorHasTag("RedTeamUnit") && TempleArr[i]->ActorHasTag("BlueTeamTample"))
		//	{
		//		Blackboard->SetValueAsObject(ADefaultUnitAI::MovingObjectPosKey, TempleArr[i]);
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
	//UE_LOG(LogTemp, Log, TEXT("UnitTurnEndstart"));
	LifeTime = 0;
	BrainComponent->StopLogic("Unit Turn End");
}

void ADefaultUnitAI::StartUnitTurn()
{
	UE_LOG(LogTemp, Log, TEXT("UnitTurnEnd"));
	if (LifeTime > 0)
	{
		BrainComponent->RestartLogic();
	}
}

void ADefaultUnitAI::EndUnitTurn()
{
	UnitTurnEndDelegate.Broadcast();
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