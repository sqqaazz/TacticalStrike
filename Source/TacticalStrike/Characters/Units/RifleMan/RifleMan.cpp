// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleMan.h"
#include "RifleManAI.h"
#include "RifleAnim.h"
//#include "UnitWidget.h"
//#include "UnitStatComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "TacticalStrikeGameInstance.h"

ARifleMan::ARifleMan()
{
	PrimaryActorTick.bCanEverTick = false;
	UnitType = 1;

	RifleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RifleMan_Weapon"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleManMesh(TEXT("SkeletalMesh'/Game/OrcaGamesFullAnimBundle/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (RifleManMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(RifleManMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Rifle_Mesh(TEXT("StaticMesh'/Game/3DModels/SniperRifle/Source/Rifle.Rifle'"));
	if (Rifle_Mesh.Succeeded())
	{
		RifleMesh->SetStaticMesh(Rifle_Mesh.Object);
	}
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> RifleManAnim(TEXT("AnimBlueprint'/Game/Blueprints/Animation/RifleAnim.RifleAnim_C'"));
	if (RifleManAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(RifleManAnim.Class);
	}

	static ConstructorHelpers::FClassFinder<ARifleManBullet> Spawning_Bullet(TEXT("Blueprint'/Game/Blueprints/Effect/BP_MyRifleManBullet.BP_MyRifleManBullet_C'"));
	if (Spawning_Bullet.Succeeded())
	{
		RifleMan_Bullet = Spawning_Bullet.Class;
	}

	HandSocket = FName(TEXT("RightHandSocket"));
	GunShootSocket = FName(TEXT("GunShoot"));

	

	MuzzleOffset = FVector(140.0f, 0.0f, -65.0f);

	//RifleMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
	RifleMesh->SetupAttachment(GetMesh(), HandSocket);
	RifleMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 1.5f));
	RifleMesh->SetRelativeRotation(FRotator(-3.0f, 90.0f, 10.0f));

	HPBarWidget->SetupAttachment(GetMesh());
	AIControllerClass = ARifleManAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ARifleMan::BeginPlay()
{
	Super::BeginPlay();

	FVector SocketLocation = RifleMesh->GetSocketLocation(HandSocket);
	//UE_LOG(LogTemp, Log, TEXT("%f, %f, %f"), SocketLocation.X, SocketLocation.Y, SocketLocation.Z);

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
}

float ARifleMan::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP = FMath::Clamp(int32(CurrentHP - FinalDamage), 0, MaxHP);
	OnUnitHPChanged.Broadcast(this);
	if (CurrentHP < 1)
	{
		auto AnimInstance = Cast<URifleAnim>(GetMesh()->GetAnimInstance());
		if (nullptr != AnimInstance)
			AnimInstance->IsDead = true;

		ACommanderController* CommanderController = Cast<ACommanderController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CommanderController != nullptr)
			CommanderController->SetDefaultObjectInfo();

		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
		auto AIController = Cast<ARifleManAI>(this->GetController());
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

void ARifleMan::AttackCheck()
{
	Super::AttackCheck();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("aaa")));
	if (RifleMan_Bullet)
	{
		FVector ViewLocation;
		FRotator ViewRotation;
		GetActorEyesViewPoint(ViewLocation, ViewRotation);
		FVector MuzzleLocation = ViewLocation + FTransform(ViewRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = ViewRotation;
		//MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = this;
			ARifleManBullet* SpawnBullet = World->SpawnActor<ARifleManBullet>(RifleMan_Bullet, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (SpawnBullet)
			{
				if (this->ActorHasTag("BlueTeamUnit"))
				{
					SpawnBullet->Tags.Add("BlueTeamProjectile");
				}
				else if (this->ActorHasTag("RedTeamUnit"))
				{
					SpawnBullet->Tags.Add("RedTeamProjectile");
				}
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("ccc")));
				FVector LaunchDirection(MuzzleRotation.Vector());
				SpawnBullet->FireInDirection(LaunchDirection);
			}
		}

	}
}

float ARifleMan::GetHealthRatio()
{
	Super::GetHealthRatio();

	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (float(CurrentHP) / float(MaxHP));
}