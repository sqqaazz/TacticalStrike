// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Animation/AnimInstance.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAnim.h"
#include "SwordManAnim.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API USwordManAnim : public UDefaultUnitAnim
{
	GENERATED_BODY()
	
public:
	USwordManAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	//bool IsAttacking;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	//bool IsDetect;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	//bool IsDead;

protected:

	UFUNCTION()
	virtual void AnimNotify_Ready() override;

	UFUNCTION()
	virtual void AnimNotify_NotReady() override;

	//UFUNCTION()
	//virtual void AnimNotify_Attack() override;
private:

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	//bool IsWalking;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	//bool IsRunning;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	//bool IsReady;

	//UPROPERTY()
	//APawn* Pawn;
};
