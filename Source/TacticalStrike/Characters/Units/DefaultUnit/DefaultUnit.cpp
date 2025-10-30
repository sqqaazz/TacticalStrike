// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultUnit.h"
#include "Blueprint/UserWidget.h"
#include "DefaultUnitAnim.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ADefaultUnit::ADefaultUnit()
{
	PrimaryActorTick.bCanEverTick = false;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DefaultUnit_HpBarWidget"));
	//UnitSelectedWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DefaultUnit_UnitSelectedWidget"));
	UnitClickableComponent = CreateDefaultSubobject<UUnitClickableComponent>(TEXT("UnitClickableComponent_DefaultUnit"));
	NiagaraComponent_ObjectSelected = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_DefaultUnit_ObjectSelected"));
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene_DefaultUnit"));

	static ConstructorHelpers::FClassFinder<UUnitWidget> HealthUI(TEXT("WidgetBlueprint'/Game/Blueprints/Widgets/BP_HealthUI.BP_HealthUI_C'"));
	if (HealthUI.Succeeded())
	{
		HPBarWidget->SetWidgetClass(HealthUI.Class);
		HPBarWidget->SetDrawSize(FVector2D(100.0f, 30.0f));
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Selected(TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/Niagara/Niagara_ObjectSelected.Niagara_ObjectSelected'"));
	if (Selected.Succeeded())
	{
		NiagaraSystem_ObjectSelected = Selected.Object;
		NiagaraComponent_ObjectSelected->SetAsset(NiagaraSystem_ObjectSelected);
		NiagaraComponent_ObjectSelected->bAutoActivate = true;
	}

	//static ConstructorHelpers::FClassFinder<UUserWidget> SelectedUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widgets/BP_UnitSelectedUI.BP_UnitSelectedUI_C'"));
	//if (SelectedUI.Succeeded())
	//{
	//	UnitSelectedWidget->SetWidgetClass(SelectedUI.Class);
	//	UnitSelectedWidget->SetDrawSize(FVector2D(300.0f, 300.0f));
	//}

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	//UnitSelectedWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	//UnitSelectedWidget->SetWidgetSpace(EWidgetSpace::World);

	RootComponent = RootScene;
	HPBarWidget->SetupAttachment(RootScene);
	NiagaraComponent_ObjectSelected->SetupAttachment(RootScene);
	GetMesh()->SetupAttachment(RootScene);
	GetCapsuleComponent()->SetupAttachment(RootScene);
	//UnitSelectedWidget->SetupAttachment(RootScene);

	GetCharacterMovement()->MaxWalkSpeed = 400;
	DeadTimer = 3.0f;
	DeathState = false;

	NiagaraComponent_ObjectSelected->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
	SetActorRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
}

void ADefaultUnit::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("Unit");

	Set_NiagaraComponent_ObjectSelected_Scale();
	Set_NiagaraComponent_ObjectSelected_Visibility(false);

	auto CharacterWidget = Cast<UUnitWidget>(HPBarWidget->GetUserWidgetObject());

	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindUnitWidget(this);
	}
}

void ADefaultUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ADefaultUnit::GetHealthRatio()
{
	return 0.7f;
}

void ADefaultUnit::AttackCheck()
{

}

void ADefaultUnit::Attacking()
{
	auto AnimInstance = Cast<UDefaultUnitAnim>(GetMesh()->GetAnimInstance());
	if (nullptr != AnimInstance)
	{
		AnimInstance->IsAttacking = true;
	}
}

void ADefaultUnit::EndAttack()
{
	OnAttackEnd.Broadcast();
}

void ADefaultUnit::SetUnitCustomDepth(bool Result)
{
	USkeletalMeshComponent* UnitSkeletalMesh = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (UnitSkeletalMesh != nullptr)
	{
		if (Result)
		{
			UnitSkeletalMesh->SetRenderCustomDepth(true);
		}
		else
			UnitSkeletalMesh->SetRenderCustomDepth(false);
	}
}

void ADefaultUnit::Set_NiagaraComponent_ObjectSelected_Scale()
{
	float NiagaraScale = 1.0f;

	NiagaraComponent_ObjectSelected->SetVariableFloat(FName("MeshUniformScale"), NiagaraScale);
	NiagaraComponent_ObjectSelected->Activate(true);
}

void ADefaultUnit::Set_NiagaraComponent_ObjectSelected_Visibility(bool Visibility)
{
	if (Visibility)
	{
		//NiagaraComponent_ObjectSelected->Deactivate();
		//NiagaraComponent_ObjectSelected->Activate(true);
		NiagaraComponent_ObjectSelected->SetVisibility(true);
	}
	else
	{
		NiagaraComponent_ObjectSelected->SetVisibility(false);
		//NiagaraComponent_ObjectSelected->Deactivate();
	}
}