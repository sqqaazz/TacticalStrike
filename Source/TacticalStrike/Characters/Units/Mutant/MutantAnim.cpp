// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantAnim.h"

UMutantAnim::UMutantAnim()
{

	IsWalking = false;
	IsAttacking = false;
	IsDead = false;
}

void UMutantAnim::NativeUpdateAnimation(float DeltaSeconds)
{
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