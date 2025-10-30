// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Default_Range.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAI.h"
#include "Objects/Tample/DefaultTample.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_Default_Range::UBTDecorator_Default_Range()
{
	NodeName = TEXT("Unit_CanAttack");
}

bool UBTDecorator_Default_Range::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Pawn = Cast<ADefaultUnit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Pawn)
		return false;
	uint8 UnitType = Pawn->UnitType;

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADefaultUnitAI::TargetKey));
	if (nullptr == Target)
		return false;

	UTacticalStrikeGameInstance* GameInstance = Cast<UTacticalStrikeGameInstance>(OwnerComp.GetAIOwner()->GetWorld()->GetGameInstance());
	FUnitTableRow* UnitDataInfo;
	if (GameInstance != nullptr)
	{
		UnitDataInfo = GameInstance->GetUnitTable(UnitType);
		ADefaultTample* Tample = Cast<ADefaultTample>(Target);
		if (Tample != nullptr)
		{
			if (Target->GetDistanceTo(Pawn) - 1700.0f <= UnitDataInfo->Range)
				return true;
			else
				return false;
		}
		else
		{
			//UE_LOG(LogTemp, Log, TEXT("@@@@@@@@@@@@@@@@@Distance:%f"), Target->GetDistanceTo(Pawn));
			if (Target->GetDistanceTo(Pawn) <= UnitDataInfo->Range)
				return true;
			else
				return false;
		}
	}
	else
		return false;

	return bResult;
}