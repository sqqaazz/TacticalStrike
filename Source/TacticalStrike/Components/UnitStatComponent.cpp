// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitStatComponent.h"

// Sets default values for this component's properties
UUnitStatComponent::UUnitStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UUnitStatComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UUnitStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetUnitStat();
}


// Called every frame
/*
void UUnitStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

void UUnitStatComponent::SetUnitStat()
{
	
}

void UUnitStatComponent::SetDamage(float NewDamage)
{
	UE_LOG(LogTemp, Log, TEXT("name"));
	UE_LOG(LogTemp, Log, TEXT("name: %s"), *GetOwner()->GetName());
}