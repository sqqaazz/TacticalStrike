// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUnit.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainMenuUnit::AMainMenuUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainMenuCamera"));
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainMenuCameraSpringArm"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainMenuUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AMainMenuUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

