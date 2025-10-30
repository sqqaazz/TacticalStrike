// Fill out your copyright notice in the Description page of Project Settings.


#include "Mutant.h"
//#include "UnitWidget.h"
#include "Components/WidgetComponent.h"
//#include "TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MutantAI.h"
#include "MutantAnim.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"

AMutant::AMutant()
{
	PrimaryActorTick.bCanEverTick = false;
	UnitType = 3;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MutantMesh(TEXT("SkeletalMesh'/Game/3DModels/Character/Mutant/Mutant.Mutant'"));

	if (MutantMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MutantMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> MutantAnim(TEXT("AnimBlueprint'/Game/Blueprints/Animation/MutantAnim.MutantAnim_C'"));
	if (MutantAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MutantAnim.Class);
	}

	HPBarWidget->SetupAttachment(GetMesh());

	GetCapsuleComponent()->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	AIControllerClass = AMutantAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	//HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void AMutant::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));


	if (GameInstance != nullptr)
	{
		UnitDataInfo = GameInstance->GetUnitTable(UnitType);
		Attack = UnitDataInfo->Attack;
		Armor = UnitDataInfo->Armor;
		MaxHP = UnitDataInfo->MaxHP;
		Speed = UnitDataInfo->Speed;
		CurrentHP = MaxHP;

		ObjectInfo.BuildTime = UnitDataInfo->BuildTime;
		ObjectInfo.CurrentBuildTime = 0;
		ObjectInfo.CurrentHP = MaxHP;
		ObjectInfo.ObjectState = EObjectState::None;
		ObjectInfo.ObjectType = UnitType;
		ObjectInfo.ObjectActor = this;
	}
}

float AMutant::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP = FMath::Clamp(int32(CurrentHP - (FinalDamage - Armor)), 0, MaxHP);
	OnUnitHPChanged.Broadcast(this);
	if (CurrentHP < 1)
	{
		auto AnimInstance = Cast<UMutantAnim>(GetMesh()->GetAnimInstance());
		if (nullptr != AnimInstance)
			AnimInstance->IsDead = true;
		
		ACommanderController* CommanderController = Cast<ACommanderController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CommanderController != nullptr)
			CommanderController->SetDefaultObjectInfo();

		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
		auto AIController = Cast<AMutantAI>(this->GetController());
		if (AIController != nullptr && !DeathState)
		{
			DeathState = true;
			AIController->StopAI();
			this->Tags.Empty();
			GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
				Destroy();
			}), DeadTimer, false);
		}
	}

	return FinalDamage;
}

void AMutant::AttackCheck()
{
	Super::AttackCheck();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_WorldStatic;
	float AttackRadius = 70.0f;

	if (this->ActorHasTag("BlueTeamUnit"))
		TraceChannel = ECollisionChannel::ECC_GameTraceChannel10;
	else if (this->ActorHasTag("RedTeamUnit"))
		TraceChannel = ECollisionChannel::ECC_GameTraceChannel11;

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * UnitDataInfo->Range,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

	FColor DrawColor = bResult ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(),
		GetActorLocation() + GetActorForwardVector() * UnitDataInfo->Range * 0.5f,
		UnitDataInfo->Range * 0.5f + AttackRadius,
		AttackRadius,
		FRotationMatrix::MakeFromZ(GetActorForwardVector() * UnitDataInfo->Range).ToQuat(),
		DrawColor,
		false,
		2.0f);

	if (bResult)
	{
		if (HitResult.GetActor())
		{
			///FDamageEvent DamageEvent;
			///HitResult.GetActor()->TakeDamage(UnitDataInfo->Attack, DamageEvent, GetController(), this);

			UGameplayStatics::ApplyDamage(HitResult.GetActor(), UnitDataInfo->Attack, GetController(), nullptr, NULL);
		}
	}
}

float AMutant::GetHealthRatio()
{
	Super::GetHealthRatio();

	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (float(CurrentHP) / float(MaxHP));
}