// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "RifleManBullet.h"
//#include "Animation/AnimInstance.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAnim.h"
#include "RifleAnim.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API URifleAnim : public UDefaultUnitAnim
{
	GENERATED_BODY()

public:
	URifleAnim();

	//virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	//bool IsAttacking;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	//bool IsDead;

protected:
	//UFUNCTION()
	//virtual void AnimNotify_Attack() override;

	/*UFUNCTION()
	virtual void AnimNotify_EndAttack() override;*/
private:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	//bool IsWalking;

	//UPROPERTY(VisibleAnywhere)
	//FVector MuzzleOffset;

	//UPROPERTY()
	//TSubclassOf<ARifleManBullet> RifleMan_Bullet;

	//UPROPERTY()
	//APawn* Pawn;

	//UPROPERTY()
	//ARifleManBullet* RifleManBullet;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	//UAnimMontage* WalkMontage;

	
};
