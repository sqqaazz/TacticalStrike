// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "RifleMan.h"
//#include "Mutant.h"
#include "UnitWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UUnitWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	void UpdateHealthWidget(class ADefaultUnit* ClickedDefaultUnit);

public:
	//void BindRifleManWidget(class ARifleMan* NewCharacterStat);
	void BindUnitWidget(class ADefaultUnit* NewCharacterStat);
private:
	class UProgressBar* HPProgressBar;

	//TWeakObjectPtr<class ARifleMan> CurrentCharacterStat;

	TWeakObjectPtr<class ADefaultUnit> CurrentUnitStat;
};
