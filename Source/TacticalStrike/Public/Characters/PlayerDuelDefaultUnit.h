// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerDuelDefaultUnit.generated.h"

UCLASS()
class TACTICALSTRIKE_API APlayerDuelDefaultUnit : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerDuelDefaultUnit();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* MainCamera;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* PlayerMesh;

	FVector CurrentVelocity;
};
