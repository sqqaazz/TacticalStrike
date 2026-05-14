// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderUnit.h"
#include "Controllers/CommanderController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
ACommanderUnit::ACommanderUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CommanderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CommanderMesh"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CommanderCamera"));
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CommanderCameraSpringArm"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> UnitMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));
	if (UnitMesh.Succeeded())
	{
		CommanderMesh->SetStaticMesh(UnitMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<ACommanderAI> COMMANDERAI(TEXT("/Script/CoreUObject.Class'/Script/TacticalStrike.CommanderAI'"));
	if (COMMANDERAI.Succeeded())
		CommanderAI = COMMANDERAI.Class;
	static ConstructorHelpers::FClassFinder<ATeamMainAI> TEAMMAINAI(TEXT("/Script/CoreUObject.Class'/Script/TacticalStrike.TeamMainAI'"));
	if (TEAMMAINAI.Succeeded())
		TeamMainAI = TEAMMAINAI.Class;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMapping(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/InputContext/CommanderUnitInputContext.CommanderUnitInputContext'"));
	if (InputMapping.Succeeded())
		CommanderUnitContext = InputMapping.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> INPUTACTIONVIEWTILE(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/InputAction/CommanderUnit_IA_ViewTile.CommanderUnit_IA_ViewTile'"));
	if (INPUTACTIONVIEWTILE.Succeeded())
		ViewTileAction = INPUTACTIONVIEWTILE.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> INPUTACTIONLEFTMOUSECLICKED(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/InputAction/CommanderUnit_IA_LeftMouseClicked.CommanderUnit_IA_LeftMouseClicked'"));
	if (INPUTACTIONLEFTMOUSECLICKED.Succeeded())
		LeftMouseClickedAction = INPUTACTIONLEFTMOUSECLICKED.Object;

	RootComponent = CommanderMesh;
	CameraSpringArm->SetupAttachment(RootComponent);
	MainCamera->SetupAttachment(CameraSpringArm);

	CameraSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CameraSpringArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));

	MainCamera->SetRelativeLocation(FVector(-3000.0f, 0.0f, -3000.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//CommanderController = Cast<ACommanderController>(Cast<APlayerController>(this->GetController()));
	SpringArmLength = 0.0f;

	CommanderMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void ACommanderUnit::BeginPlay()
{
	Super::BeginPlay();

	TeamMainAIInstance = GetWorld()->SpawnActor<ATeamMainAI>(TeamMainAI, FVector::ZeroVector, FRotator::ZeroRotator);
	TeamMainAIInstance->InitializeController();

	ACommanderController* CommanderController = Cast<ACommanderController>(GetController());
	if (CommanderController != nullptr)
	{
		TeamMainAIInstance->GetBlackboardComponent()->SetValueAsObject(ATeamMainAI::OwnerCommanderAIKey, CommanderController);
		TeamMainAIInstance->ObjectInfo.ObjectOwner = EObjectOwner::Blue;

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(CommanderController->GetLocalPlayer());
		//CommanderController->SetInputMode(FInputModeGameOnly());
		//CommanderController->SetInputMode(FInputModeGameAndUI());
		if (Subsystem != nullptr)
			Subsystem->AddMappingContext(CommanderUnitContext, 0);
	}

	if (GetController() == nullptr /* || !GetController()->IsA(ACommanderController::StaticClass()) */ )
	{
		ACommanderAI* NewCommanderAI = GetWorld()->SpawnActor<ACommanderAI>(CommanderAI, GetActorLocation(), GetActorRotation());
		if (NewCommanderAI != nullptr)
		{
			TeamMainAIInstance->GetBlackboardComponent()->SetValueAsObject(ATeamMainAI::OwnerCommanderAIKey, NewCommanderAI);
			TeamMainAIInstance->ObjectInfo.ObjectOwner = EObjectOwner::Red;

			NewCommanderAI->Possess(this);
			//UE_LOG(LogTemp, Log, TEXT("AICommander"));
		}
	}
}
// Called to bind functionality to input
void ACommanderUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* InputAction = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (InputAction != nullptr)
	{
		InputAction->BindAction(ViewTileAction, ETriggerEvent::Triggered, this, &ACommanderUnit::ViewTile);
		InputAction->BindAction(LeftMouseClickedAction, ETriggerEvent::Triggered, this, &ACommanderUnit::LeftMouseClicked);
	}

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACommanderUnit::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACommanderUnit::MoveRight);

	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACommanderUnit::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACommanderUnit::ZoomOut);
}


// Called every frame
void ACommanderUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	
	if (FMath::Abs(CameraSpringArm->TargetArmLength - SpringArmLength) > KINDA_SMALL_NUMBER)
	{
		CameraSpringArm->TargetArmLength = FMath::Lerp(CameraSpringArm->TargetArmLength, SpringArmLength, 0.05f);
	}

}

void ACommanderUnit::ViewTile(const FInputActionInstance& Instance)
{
	ACommanderController* CommanderController = Cast<ACommanderController>(GetController());
	if (CommanderController != nullptr)
	{
		CommanderController->ViewGridTile();
	}
}

void ACommanderUnit::LeftMouseClicked(const FInputActionInstance& Instance)
{
	ACommanderController* CommanderController = Cast<ACommanderController>(GetController());
	if (CommanderController != nullptr)
	{
		CommanderController->OnClickedEvent();
	}
}

void ACommanderUnit::MoveForward(float AxisValue)
{
	//UE_LOG(LogTemp, Log, TEXT("vvv"));
	//AddMovementInput(GetActorForwardVector(), AxisValue);
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 5000.0f;
}

void ACommanderUnit::MoveRight(float AxisValue)
{
	//AddMovementInput(GetActorRightVector(), AxisValue);
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 5000.0f;
}

void ACommanderUnit::ZoomIn()
{
	SpringArmLength = FMath::Clamp(SpringArmLength - 500.0f, -4000.0f, 2500.0f);
}

void ACommanderUnit::ZoomOut()
{
	SpringArmLength = FMath::Clamp(SpringArmLength + 500.0f, -4000.0f, 2500.0f);
}

