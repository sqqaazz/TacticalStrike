// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainMenuController();

	UPROPERTY(VisibleAnywhere, Category = UI)
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;

	class UMainMenuWidget* MainMenuWidget;

	UFUNCTION(BlueprintCallable)
	void StartSequence();

	UFUNCTION(BlueprintCallable)
	void EndSequence();

protected:
	virtual void BeginPlay() override;
};
