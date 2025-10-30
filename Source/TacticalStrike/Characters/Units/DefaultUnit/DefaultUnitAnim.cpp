// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultUnitAnim.h"
#include "DefaultUnit.h"

UDefaultUnitAnim::UDefaultUnitAnim()
{
	IsAttacking = false;
	IsDead = false;
	IsWalking = false;
	IsReady = false;
	IsDetect = false;
}

void UDefaultUnitAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	else
	{
		if (!Pawn->GetVelocity().IsZero())
		{
			IsWalking = true;
		}
		else
		{
			IsWalking = false;
		}
	}
}

void UDefaultUnitAnim::AnimNotify_Ready()
{

}

void UDefaultUnitAnim::AnimNotify_NotReady()
{

}

void UDefaultUnitAnim::AnimNotify_Attack()
{
	auto DefaultUnit = Cast<ADefaultUnit>(TryGetPawnOwner());
	if (DefaultUnit != nullptr)
	{
		DefaultUnit->AttackCheck();
	}
}

void UDefaultUnitAnim::DetectEnemy()
{
	IsDetect = true;
}

void UDefaultUnitAnim::DontDetectEnemy()
{
	IsDetect = false;
}

void UDefaultUnitAnim::AnimNotify_EndAttack()
{
	auto DefaultPawn = Cast<ADefaultUnit>(TryGetPawnOwner());
	if (DefaultPawn != nullptr)
	{
		DefaultPawn->EndAttack();
		IsAttacking = false;
	}
}