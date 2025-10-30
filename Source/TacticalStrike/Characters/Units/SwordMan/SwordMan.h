// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "SwordMan.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API ASwordMan : public ADefaultUnit
{
	GENERATED_BODY()
	
public:
	ASwordMan();
protected:
	virtual void BeginPlay() override;
	virtual float GetHealthRatio() override;

	//공격 시 판정
	virtual void AttackCheck() override;
public:
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void EquipWeapon();
	void UnEquipWeapon();

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
			class AController* EventInstigator, AActor* DamageCauser) override;
private:
	//uint8 UnitType;

	class UTacticalStrikeGameInstance* GameInstance;
	FUnitTableRow* UnitDataInfo;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SwordMesh;

	FName HandSocket;
	FName BackSocket;
};
