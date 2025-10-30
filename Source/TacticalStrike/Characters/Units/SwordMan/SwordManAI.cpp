// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordManAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ASwordManAI::ASwordManAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Blueprints/AI/BB_SwordMan.BB_SwordMan'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Blueprints/AI/BT_SwordMan.BT_SwordMan'"));
	if (BBObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}