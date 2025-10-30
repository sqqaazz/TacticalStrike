// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_RifleMan_AttackRange.h"
#include "RifleManAI.h"
#include "RifleMan.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_RifleMan_AttackRange::UBTDecorator_RifleMan_AttackRange() 
{
	NodeName = TEXT("RifleMan_CanAttack");
}

bool UBTDecorator_RifleMan_AttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;
	auto Target = Cast<ARifleMan>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ARifleManAI::TargetKey));
	if (nullptr == Target)
		return false;
	//bResult = (Target->GetDistanceTo(ControllingPawn) <= 3000.0f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("DeltaHeight : %f"), Target->GetDistanceTo(ControllingPawn)));
	if (Target->GetDistanceTo(ControllingPawn) <= 1000.0f)
		return true;
	else
		return false;
	return bResult;

}