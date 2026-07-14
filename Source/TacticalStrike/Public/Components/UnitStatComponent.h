// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALSTRIKE_API UUnitStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitStatComponent();

	void SetUnitStat();
	void SetDamage(float NewDamage);
	FOnHPZeroDelegate HPZero;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	int32 DefaultHealth;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	int32 Health;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	int32 Armor;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	int32 Attack;
};
