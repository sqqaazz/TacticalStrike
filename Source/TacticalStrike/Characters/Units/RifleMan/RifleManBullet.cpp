// Fill out your copyright notice in the Description page of Project Settings.

#include "RifleManBullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARifleManBullet::ARifleManBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//메시와 콜리전 할당
	BulletCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RifleManBulletCollision"));
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RifleManBulletMesh"));
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("RifleManBulletMovement"));
	BulletTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RifleManBulletTrail"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Bullet_Mesh(TEXT("StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_762x51.SM_Shell_762x51'"));
	if (Bullet_Mesh.Succeeded())
	{
		BulletMesh->SetStaticMesh(Bullet_Mesh.Object);
	}
	//트레일 파티클 할당
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Bullet_Trail(TEXT("ParticleSystem'/Game/Effects/Trail/T_BulletTrail.T_BulletTrail'"));
	if (Bullet_Trail.Succeeded())
	{
		BulletTrail->SetTemplate(Bullet_Trail.Object);
	}

	RootComponent = BulletCollision;
	BulletMesh->SetupAttachment(BulletCollision);
	BulletTrail->SetupAttachment(BulletMesh);
	//콜리전 설정
	BulletCollision->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	BulletMesh->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	//BulletCollision->SetNotifyRigidBodyCollision(true);
	//projectile관련 설정
	BulletMovement->SetUpdatedComponent(BulletCollision);
	BulletMovement->InitialSpeed = 1000.0f;
	BulletMovement->MaxSpeed = 1000.0f;
	BulletMovement->ProjectileGravityScale = 0;
	BulletMovement->bRotationFollowsVelocity = true;

	//발사체 수명, 3초 설정.
	InitialLifeSpan = 3.0f;
	//발사체 메시와 콜리전의 크기와 위치 설정
	BulletMesh->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	BulletMesh->SetRelativeRotation(FRotator(-90.0f, 90.0f, 180.0f));
	//BulletCollision->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	BulletCollision->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	//히트 이벤트 델리게이트 설정
	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ARifleManBullet::OnOverlapBegin);

	//탄환 트레일 이펙트 설정
	//TrailStart = BulletMesh->GetAllSocketNames()[0];
	//TrailEnd = BulletMesh->GetAllSocketNames()[1];
}

// Called when the game starts or when spawned
void ARifleManBullet::BeginPlay()
{
	Super::BeginPlay();
	//BulletTrail->BeginTrails(TrailStart, TrailEnd, ETrailWidthMode::ETrailWidthMode_FromFirst, 10.0f);
}

/*
void ARifleManBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
void ARifleManBullet::FireInDirection(const FVector& ShootDirection)
{
	//발사시 움직임 설정
	BulletMovement->Velocity = ShootDirection * BulletMovement->InitialSpeed;
}

//피격 이벤트 설정
void ARifleManBullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (this->ActorHasTag("RedTeamProjectile"))
		{
			if (OtherActor->ActorHasTag("BlueTeamUnit") || OtherActor->ActorHasTag("BlueTeamBuilding"))
			{
				///FDamageEvent DamageEvent;
				//OtherActor->TakeDamage(20.0f, DamageEvent, nullptr, this);

				UGameplayStatics::ApplyDamage(OtherActor, 20.0f, nullptr, nullptr, NULL);
				Destroy();
			}
		}
		else if (this->ActorHasTag("BlueTeamProjectile"))
		{
			if (OtherActor->ActorHasTag("RedTeamUnit") || OtherActor->ActorHasTag("RedTeamBuilding"))
			{
				////FDamageEvent DamageEvent;
				//OtherActor->TakeDamage(20.0f, DamageEvent, nullptr, this);
				UGameplayStatics::ApplyDamage(OtherActor, 20.0f, nullptr, nullptr, NULL);
				Destroy();
			}
		}

		//if (OtherActor->ActorHasTag("RedTeamUnit") || OtherActor->ActorHasTag("BlueTeamUnit"))
		//{

		//	if ((OtherActor->ActorHasTag("RedTeamUnit") || OtherActor->ActorHasTag("RedTeamBuilding")) && this->ActorHasTag("RedTeamProjectile"))
		//		return;
		//	if ((OtherActor->ActorHasTag("BlueTeamUnit") || OtherActor->ActorHasTag("BlueTeamBuilding")) && this->ActorHasTag("BlueTeamProjectile"))
		//		return;
		//	FDamageEvent DamageEvent;
		//	OtherActor->TakeDamage(20.0f, DamageEvent, nullptr, this);
		//	UE_LOG(LogTemp, Log, TEXT("Name: %s"), *OtherActor->GetName());
		//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("2")));
		//	Destroy();
		//}
	}
}