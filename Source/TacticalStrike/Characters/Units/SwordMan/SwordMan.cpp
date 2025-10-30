// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordMan.h"
//#include "UnitWidget.h"
#include "Components/WidgetComponent.h"
//#include "TacticalStrikeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SwordManAI.h"
#include "SwordManAnim.h"
#include "DrawDebugHelpers.h"

ASwordMan::ASwordMan()
{
	PrimaryActorTick.bCanEverTick = false;
	UnitType = 2;

	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMan_Weapon"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordManMesh(TEXT("SkeletalMesh'/Game/3DModels/Character/Default/_SK_Mannequin_Mixamo._SK_Mannequin_Mixamo'"));
	if (SwordManMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SwordManMesh.Object);
	}
	

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sword_Mesh(TEXT("StaticMesh'/Game/3DModels/StaticMesh/Weapons/GreatSword/low_uv_sep_SFGS_low002.low_uv_sep_SFGS_low002'"));
	if (Sword_Mesh.Succeeded())
	{
		SwordMesh->SetStaticMesh(Sword_Mesh.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> SwordManAnim(TEXT("AnimBlueprint'/Game/Blueprints/Animation/SwordMan_Anim.SwordMan_Anim_C'"));
	if (SwordManAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(SwordManAnim.Class);
	}

	//HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	//HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	HPBarWidget->SetupAttachment(GetMesh());

	HandSocket = TEXT("RightHandSocket");
	BackSocket = TEXT("SpineSocket");

	//SwordMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BackSocket);
	SwordMesh->SetupAttachment(GetMesh(), BackSocket);
	SwordMesh->SetRelativeLocation(FVector(-130.0f, -20.0f, -15.0f));
	SwordMesh->SetRelativeRotation(FRotator(-80.0f, 0.0f, 0.0f));

	AIControllerClass = ASwordManAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASwordMan::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance != nullptr)
	{
		UnitDataInfo = GameInstance->GetUnitTable(UnitType);
		UnitName = UnitDataInfo->Name;
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
	//OnUnitHPChanged.Broadcast();
}

float ASwordMan::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP = FMath::Clamp(int32(CurrentHP - (FinalDamage - Armor)), 0, MaxHP);
	OnUnitHPChanged.Broadcast(this);
	if (CurrentHP < 1)
	{
		auto AnimInstance = Cast<USwordManAnim>(GetMesh()->GetAnimInstance());
		if (nullptr != AnimInstance)
			AnimInstance->IsDead = true;

		ACommanderController* CommanderController = Cast<ACommanderController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CommanderController != nullptr)
			CommanderController->SetDefaultObjectInfo();
		
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

		auto AIController = Cast<ASwordManAI>(this->GetController());
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

void ASwordMan::AttackCheck()
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
			//FDamageEvent DamageEvent;
			//HitResult.GetActor()->TakeDamage(UnitDataInfo->Attack, DamageEvent, GetController(), this);
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), UnitDataInfo->Attack, GetController(), nullptr, NULL);
		}
	}
}

void ASwordMan::EquipWeapon()
{
	SwordMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
	const USkeletalMeshSocket* EquipWeaponSocekt = GetMesh()->GetSocketByName(HandSocket);
	//if (EquipWeaponSocekt != nullptr)
	//	EquipWeaponSocekt->AttachActor(nullptr, SwordMesh);
	// 
	// 
	//SwordMesh->SetupAttachment(GetMesh(), HandSocket);
	//SwordMesh->SetRelativeLocation(FVector(-96.13f, -21.84f, 136.29f));
	//SwordMesh->SetRelativeRotation(FRotator(-30.0f, -133.54f, -195.5f));

	//SwordMesh->SetRelativeLocation(FVector(144.258f, 70.883f, 12.488f));
	//SwordMesh->SetRelativeRotation(FRotator(94.0f, 0.0f, 96.789));

	//SwordMesh->SetRelativeLocation(FVector(96.53f, -111.5f, 69.62f));
	//SwordMesh->SetRelativeRotation(FRotator(27.58f, -151.8f, -104.5));
}

void ASwordMan::UnEquipWeapon()
{
	//SwordMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BackSocket);
	SwordMesh->SetupAttachment(GetMesh(), BackSocket);
	SwordMesh->SetRelativeLocation(FVector(-130.0f, -20.0f, -15.0f));
	SwordMesh->SetRelativeRotation(FRotator(-80.0f, 0.0f, 0.0f));
}


float ASwordMan::GetHealthRatio()
{
	Super::GetHealthRatio();

	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (float(CurrentHP) / float(MaxHP));
}