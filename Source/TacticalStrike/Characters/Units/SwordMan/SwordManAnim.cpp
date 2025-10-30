// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordManAnim.h"
#include "SwordMan.h"

USwordManAnim::USwordManAnim()
{

}

void USwordManAnim::NativeUpdateAnimation(float DeltaSeconds)
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

void USwordManAnim::AnimNotify_Ready()
{
	Super::AnimNotify_Ready();
	IsReady = true;
	//UE_LOG(LogTemp, Log, TEXT("Ready"));
	auto SwordMan = Cast<ASwordMan>(TryGetPawnOwner());
	if (SwordMan != nullptr)
	{
		SwordMan->EquipWeapon();
	}
}

void USwordManAnim::AnimNotify_NotReady()
{
	Super::AnimNotify_NotReady();
	IsReady = false;
	auto SwordMan = Cast<ASwordMan>(TryGetPawnOwner());
	if (SwordMan != nullptr)
	{
		SwordMan->UnEquipWeapon();
	}
}

//void USwordManAnim::AnimNotify_Attack()
//{
//	Super::AnimNotify_Attack();
//	auto SwordMan = Cast<ASwordMan>(TryGetPawnOwner());
//	if (SwordMan != nullptr)
//	{
//
//	}
//
//}