// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UResourceWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateResourceState();

private:
	class UTextBlock* MineralText;
	class UTextBlock* GasText;

	class ACommanderController* PlayerController;
};
