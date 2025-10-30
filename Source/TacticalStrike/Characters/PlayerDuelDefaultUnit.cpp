// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDuelDefaultUnit.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerDuelDefaultUnit::APlayerDuelDefaultUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DuelPlayerMesh"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DuelPlayerCamera"));
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("DuelPlayerCameraSpringArm"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> UnitMesh(TEXT("SkeletalMesh'/Game/Greatsword_Animation/Demo/Mannequin/Character/Mesh/SK_Mannequin_Sword_Sheath.SK_Mannequin_Sword_Sheath'"));
	if (UnitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(UnitMesh.Object);
	}

	//RootComponent = GetMesh();
	CameraSpringArm->SetupAttachment(RootComponent);
	MainCamera->SetupAttachment(CameraSpringArm);

	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	CameraSpringArm->SetRelativeLocation(FVector(0.0f, -20.0f, 100.0f));
	CameraSpringArm->SetRelativeRotation(FRotator(-45.0f,90.0f, 0.0f));

	MainCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	CameraSpringArm->bUsePawnControlRotation = true;
	MainCamera->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void APlayerDuelDefaultUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerDuelDefaultUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void APlayerDuelDefaultUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerDuelDefaultUnit::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerDuelDefaultUnit::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerDuelDefaultUnit::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerDuelDefaultUnit::LookUp);
}

void APlayerDuelDefaultUnit::MoveForward(float AxisValue)
{
	//UE_LOG(LogTemp, Log, TEXT("vvv"));
	//AddMovementInput(GetActorForwardVector(), AxisValue);
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 2000.0f;
}

void APlayerDuelDefaultUnit::MoveRight(float AxisValue)
{
	//AddMovementInput(GetActorRightVector(), AxisValue);
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 2000.0f;
}

void APlayerDuelDefaultUnit::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerDuelDefaultUnit::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}
