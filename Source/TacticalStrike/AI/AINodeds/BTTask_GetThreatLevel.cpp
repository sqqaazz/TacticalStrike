// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINodeds/BTTask_GetThreatLevel.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "AI/AIController/TeamMainAI.h"
//#include "GameMode/TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DataTables/UnitDataTables.h"
#include "Components/GridTileActor.h"

UBTTask_GetThreatLevel::UBTTask_GetThreatLevel()
{
	NodeName = TEXT("GetThreatLevel");
}

EBTNodeResult::Type UBTTask_GetThreatLevel::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ADefaultUnitAI* DefaultUnitAI = Cast<ADefaultUnitAI>(OwnerComp.GetAIOwner());
	ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(OwnerComp.GetOwner());
	ATeamMainAI* TeamMainAI = Cast<ATeamMainAI>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::MainTeamAIKey));
	UTacticalStrikeGameInstance* GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (DefaultUnitAI == nullptr || DefaultUnit == nullptr || TeamMainAI == nullptr || GameInstance)
		return EBTNodeResult::Failed;

	FVector UnitLocation = DefaultUnit->GetActorLocation();
	FIntPoint UnitGridLocation = (UnitLocation.X / 100, UnitLocation.Y / 100);

	TArray<ADefaultUnit*> SightEnemyArr = TeamMainAI->SightEnemyArr;

	if (SightEnemyArr.Num() == 0)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::InPlace_bIsTargetInRange, false);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		FUnitTableRow* UnitDataInfo = GameInstance->GetUnitTable(DefaultUnit->ObjectInfo.ObjectType);
		UWorld* World = DefaultUnit->GetWorld();
		FVector Center = DefaultUnit->GetActorLocation();
		float DetectRadius = float(UnitDataInfo->Range);

		if (nullptr == World)
			return EBTNodeResult::Failed;
		TArray<FOverlapResult> OverlapResults;
		FCollisionQueryParams CollisionQueryParam(NAME_None, false, DefaultUnit);
		if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Blue)
		{
			bool bResult = World->OverlapMultiByChannel(
				OverlapResults,
				Center,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel6,
				FCollisionShape::MakeSphere(DetectRadius),
				CollisionQueryParam
			);

			if (bResult)
			{

			}
		}
		else if (DefaultUnit->ObjectInfo.ObjectOwner == EObjectOwner::Red)
		{
			bool bResult = World->OverlapMultiByChannel(
				OverlapResults,
				Center,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel7,
				FCollisionShape::MakeSphere(DetectRadius),
				CollisionQueryParam
			);
			if (bResult)
			{


			}
		}
		else
			return EBTNodeResult::Failed;

		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::DefaultUnitAI_bSightTriggerActivatedKey, false);
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ADefaultUnitAI::UnitActionTriggerKey, false);

		return EBTNodeResult::Succeeded;
	}
}