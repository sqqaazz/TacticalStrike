// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Animation/AnimInstance.h"
#include "Characters/Units/DefaultUnit/DefaultUnitAnim.h"
#include "MutantAnim.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UMutantAnim : public UDefaultUnitAnim
{
	GENERATED_BODY()
	
public:
	UMutantAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	//bool IsAttacking;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	//bool IsDead;
private:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	//bool IsWalking;

	//UPROPERTY()
	//APawn* Pawn;
};
