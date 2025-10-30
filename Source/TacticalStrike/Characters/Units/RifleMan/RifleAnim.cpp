// Fill out your copyright notice in the Description page of Project Settings.

#include "RifleAnim.h"
#include "RifleMan.h"

URifleAnim::URifleAnim()
{
	IsWalking = false;
	IsAttacking = false;
	IsDead = false;
	
	//static ConstructorHelpers::FClassFinder<ARifleManBullet> Spawning_Bullet(TEXT("Class'/Script/TacticalStrike.RifleManBullet'"));
	//if (Spawning_Bullet.Succeeded())
	//{
	//	RifleMan_Bullet = Spawning_Bullet.Class;
	//}
	
	//static ConstructorHelpers::FClassFinder<ARifleManBullet> Spawning_Bullet(TEXT("Blueprint'/Game/Blueprints/Effect/BP_MyRifleManBullet.BP_MyRifleManBullet_C'"));
	//if (Spawning_Bullet.Succeeded())
	//{
	//	RifleMan_Bullet = Spawning_Bullet.Class;
	//}
	//
	//MuzzleOffset = FVector(140.0f, 0.0f, -65.0f);
}

void URifleAnim::NativeUpdateAnimation(float DeltaSeconds)
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

//void URifleAnim::AnimNotify_Attack()
//{
//	Super::AnimNotify_Attack();
//	//auto Pawn = TryGetPawnOwner();
//	if (nullptr == Pawn)
//		return;
//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("aaa")));
//	if (RifleMan_Bullet && ::IsValid(Pawn))
//	{
//		FVector ViewLocation;
//		FRotator ViewRotation;
//		Pawn->GetActorEyesViewPoint(ViewLocation, ViewRotation);
//		FVector MuzzleLocation = ViewLocation + FTransform(ViewRotation).TransformVector(MuzzleOffset);
//		FRotator MuzzleRotation = ViewRotation;
//		//MuzzleRotation.Pitch += 10.0f;
//		UWorld* World = GetWorld();
//		if (World)
//		{
//			FActorSpawnParameters SpawnParams;
//			SpawnParams.Owner = Pawn;
//			SpawnParams.Instigator = Pawn;
//			ARifleManBullet* SpawnBullet = World->SpawnActor<ARifleManBullet>(RifleMan_Bullet, MuzzleLocation, MuzzleRotation, SpawnParams);
//			if (SpawnBullet)
//			{
//				if (Pawn->ActorHasTag("BlueTeamUnit")) 
//				{
//					SpawnBullet->Tags.Add("BlueTeamProjectile");
//				}
//				else if (Pawn->ActorHasTag("RedTeamUnit"))
//				{
//					SpawnBullet->Tags.Add("RedTeamProjectile");
//				}
//				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("ccc")));
//				FVector LaunchDirection(MuzzleRotation.Vector());
//				SpawnBullet->FireInDirection(LaunchDirection);
//			}
//		}
//		
//	}
//}

//void URifleAnim::AnimNotify_EndShoot()
//{
//	//auto Pawn = Cast<ARifleMan>(TryGetPawnOwner());
//
//	if (nullptr == Pawn)
//		return;
//	auto RiflePawn = Cast<ARifleMan>(TryGetPawnOwner());
//	if (RiflePawn != nullptr)
//	{
//		RiflePawn->EndAttack();
//
//		IsAttacking = false;
//	}
//}