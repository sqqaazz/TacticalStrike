// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RifleManBullet.generated.h"

UCLASS()
class TACTICALSTRIKE_API ARifleManBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifleManBullet();

	void FireInDirection(const FVector& ShootDirection);
protected:
	virtual void BeginPlay() override;

	//UFUNCTION()
	//void OnBeginOverlapCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//탄환 충돌 시 호출되는 함수
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	//	FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* BulletCollision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* BulletMovement;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* BulletTrail;

	//FName TrailStart;
	//FName TrailEnd;
};
