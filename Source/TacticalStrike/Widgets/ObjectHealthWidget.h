// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UObjectHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindBuildingWidget(class ADefaultBuilding* NewBuildingStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHealthWidget(class ADefaultBuilding* ClickedDefaultBuilding);
private:
	class UProgressBar* HPProgressBar;

	TWeakObjectPtr<class ADefaultBuilding> CurrentUnitStat;
};
