// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMutantAI::AMutantAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Blueprints/AI/BB_Mutant.BB_Mutant'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Blueprints/AI/BT_Mutant.BT_Mutant'"));
	if (BBObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
	//static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Blueprints/AI/BB_SwordMan.BB_SwordMan'"));
	//if (BBObject.Succeeded())
	//{
	//	BBAsset = BBObject.Object;
	//}
	//static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Blueprints/AI/BT_SwordMan.BT_SwordMan'"));
	//if (BBObject.Succeeded())
	//{
	//	BTAsset = BTObject.Object;
	//}
}