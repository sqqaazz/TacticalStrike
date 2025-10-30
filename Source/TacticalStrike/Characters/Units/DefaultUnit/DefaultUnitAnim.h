// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DefaultUnitAnim.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UDefaultUnitAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDefaultUnitAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	bool IsDetect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	bool IsDead;

	void DetectEnemy();
	void DontDetectEnemy();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	bool IsWalking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	bool IsRunning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	bool IsReady;

	virtual void AnimNotify_Ready();

	virtual void AnimNotify_NotReady();

	UFUNCTION()
	virtual void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_EndAttack();

	UPROPERTY()
	APawn* Pawn;
};
