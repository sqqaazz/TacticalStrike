// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Controllers/CommanderController.h"
#include "UnitClickableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALSTRIKE_API UUnitClickableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUnitClickableComponent();

protected:
	virtual void BeginPlay() override;

public:	
	/*virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;*/

	UFUNCTION()
	void UpdateUnitHP(ADefaultUnit* ClickedDefaultUnit);
private:
	UFUNCTION()
	void ClickEvent(AActor* TouchedActor, FKey ButtonPressed);

	USkeletalMeshComponent* MeshComponent;

	class ACommanderController* CommanderController;
	class ADefaultUnit* DefaultUnit;
};
