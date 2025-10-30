// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "Camera/CameraComponent.h"
#include "AI/AIController/CommanderAI.h"
#include "AI/AIController/TeamMainAI.h"
#include "EnhancedInputComponent.h"
#include "CommanderUnit.generated.h"

UCLASS()
class TACTICALSTRIKE_API ACommanderUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACommanderUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* MainCamera;

	TSubclassOf<ACommanderAI> CommanderAI;
	TSubclassOf<ATeamMainAI> TeamMainAI;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(VisibleAnywhere, Category = Camera)
	//USpringArmComponent* SpringArm;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ATeamMainAI* TeamMainAIInstance;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	UFUNCTION()
	void ViewTile(const FInputActionInstance& Instance);
	UFUNCTION()
	void LeftMouseClicked(const FInputActionInstance& Instance);


	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* CommanderUnitContext;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* ViewTileAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* LeftMouseClickedAction;

	UFUNCTION()
	void ZoomIn();

	UFUNCTION()
	void ZoomOut();

	FVector CurrentVelocity;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* CommanderMesh;

	float SpringArmLength;
};
