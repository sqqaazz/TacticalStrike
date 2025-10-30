// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "RifleManBullet.h"
//#include "RifleManBullet.h"
//#include "UnitDataTables.h"
#include "RifleMan.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnRifleManAttackEndDelegate);
//DECLARE_MULTICAST_DELEGATE(FOnRifleManHPChanged);
UCLASS()
class TACTICALSTRIKE_API ARifleMan : public ADefaultUnit
{
	GENERATED_BODY()
public:
	ARifleMan();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RifleMesh;
protected:
	virtual void BeginPlay() override;
	virtual float GetHealthRatio() override;

	virtual void AttackCheck() override;
public:
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

private:

	class UTacticalStrikeGameInstance* GameInstance;
	FUnitTableRow* UnitDataInfo;

	UPROPERTY(VisibleAnywhere)
	FVector MuzzleOffset;

	UPROPERTY()
	TSubclassOf<ARifleManBullet> RifleMan_Bullet;

	FName HandSocket;
	FName GunShootSocket;

	//float DeadTimer;
	//bool DeathState;
	//FTimerHandle DeadTimerHandle;
};
