// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleManAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ARifleManAI::ARifleManAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Blueprints/AI/BB_RifleMAn.BB_RifleMAn'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Blueprints/AI/BT_RifleMan.BT_RifleMan'"));
	if (BBObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}