// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataTables/UnitDataTables.h"
#include "Components/UnitClickableComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/CapsuleComponent.h"
#include "Widgets/UnitWidget.h"
#include "GameMode/TacticalStrikeGameInstance.h"
#include "Controllers/CommanderController.h"
#include "DefaultUnit.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnitHPChanged, ADefaultUnit*);
DECLARE_MULTICAST_DELEGATE(FOnDefaultUnitAttackEndDelegate);

DECLARE_MULTICAST_DELEGATE(FMovingStopDelegate);

UCLASS()
class TACTICALSTRIKE_API ADefaultUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADefaultUnit();

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* HPBarWidget;
	//UPROPERTY()
	//class UWidgetComponent* UnitSelectedWidget;

	FOnUnitHPChanged OnUnitHPChanged;

	virtual float GetHealthRatio();

	//공격 데미지 판정
	virtual void AttackCheck();

	uint8 UnitType;

	void Attacking();
	void EndAttack();

	void StartMoving(TArray <FIntPoint>& Path);
	void Moving(float DeltaTime);
	void StopMoving();
	bool bIsMoving;
	TArray<FIntPoint> CurPath;
	int32 CurPathIndex;
	FMovingStopDelegate MovingStopDelegate;

	FString UnitName;
	int32 Attack;
	int32 Armor;
	int32 MaxHP;
	int32 CurrentHP;
	int32 Speed;
	int32 BuildTime;
	int32 CurrentBuildTime;

	FObjectInfo ObjectInfo;

	FOnDefaultUnitAttackEndDelegate OnAttackEnd;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	float DeadTimer;
	bool DeathState;
	FTimerHandle DeadTimerHandle;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetUnitCustomDepth(bool Result);


	void Set_NiagaraComponent_ObjectSelected_Scale();

	void Set_NiagaraComponent_ObjectSelected_Visibility(bool Visibility);

private:
	UUnitClickableComponent* UnitClickableComponent;

	USceneComponent* RootScene;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* NiagaraComponent_ObjectSelected;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* NiagaraSystem_ObjectSelected;

};
