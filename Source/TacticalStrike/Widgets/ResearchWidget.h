// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResearchWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UResearchWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	float ResearchPercent;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	class UProgressBar* ResearchingProgressBar;
	class UTextBlock* ResearchingTextBlock;
};
