// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Mutant.generated.h"

UCLASS()
class TACTICALSTRIKE_API AMutant : public ADefaultUnit
{
	GENERATED_BODY()

public:
	AMutant();
protected:
	virtual void BeginPlay() override;
	virtual float GetHealthRatio() override;

	virtual void AttackCheck() override;
public:	
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;
private:

	class UTacticalStrikeGameInstance* GameInstance;
	FUnitTableRow* UnitDataInfo;

};
