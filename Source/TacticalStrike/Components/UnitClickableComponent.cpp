// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitClickableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"

UUnitClickableComponent::UUnitClickableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UUnitClickableComponent::BeginPlay()
{
	Super::BeginPlay();
	DefaultUnit = Cast<ADefaultUnit>(GetOwner());
	MeshComponent = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	CommanderController = Cast<ACommanderController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (MeshComponent != nullptr && DefaultUnit != nullptr)
	{
		DefaultUnit->OnClicked.AddDynamic(this, &UUnitClickableComponent::ClickEvent);
		DefaultUnit->OnUnitHPChanged.AddUObject(this, &UUnitClickableComponent::UpdateUnitHP);
	}

	if (DefaultUnit != nullptr)
	{
	}
	//UE_LOG(LogTemp, Log, TEXT("dddddddd"));
}


//void UUnitClickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

void UUnitClickableComponent::ClickEvent(AActor* TouchedActor, FKey ButtonPressed)
{
	//auto UnitInfo = Cast<ADefaultUnit>(TouchedActor);
	//if (UnitInfo != nullptr && CommanderController != nullptr)
	//{
	//	CommanderController->UpdateObjectInfo(UnitInfo->UnitType, UnitInfo->CurrentHP);
	//	CommanderController->ClickedDefaultObject = TouchedActor;

	//	CommanderController->SetObjectHighlight(TouchedActor, true);
	//	//CommanderController->ClickedDefaultObject = UnitInfo;
	//	//UpdateUnitHP(DefaultUnit);
	//}
	
	//TArray<AActor*> ActorsToFind;
	//if (UWorld* World = GetWorld())
	//{
	//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsToFind);
	//	for (AActor* Actorlist : ActorsToFind)
	//	{
	//		if (UUnitClickableComponent* CheckComponent =
	//			Cast<UUnitClickableComponent>(Actorlist->GetComponentByClass(UUnitClickableComponent::StaticClass())))
	//		{
	//			if (Actorlist != TouchedActor)
	//			{
	//				CheckComponent->MeshComponent->SetRenderCustomDepth(false);
	//			}
	//		}
	//		else
	//			continue;
	//	}
	//}

	//MeshComponent->SetRenderCustomDepth(true);
}

void UUnitClickableComponent::UpdateUnitHP(ADefaultUnit* ClickedDefaultUnit)
{
	if (DefaultUnit != nullptr && CommanderController != nullptr && CommanderController->ClickedDefaultObject == ClickedDefaultUnit)
	{
		FObjectInfo ClickedObjectInfo(ClickedDefaultUnit->ObjectInfo);
		//FObjectInfo ClickedObjectInfo(DefaultUnit->UnitType, DefaultUnit->CurrentHP, EObjectState::Activated, 0, 0, DefaultUnit);
		CommanderController->UpdateObjectInfo(ClickedObjectInfo);
	}
}