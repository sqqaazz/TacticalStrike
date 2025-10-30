// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingTimeWidget.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API UBuildingTimeWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;

public:
	//void SetProgressbar(int32 CurrentTime, int32 BuildingTime);

	void UpdateBuildTime(int32 CurrentTime, int32 BuildingTime);
private:
	class UProgressBar* BuildingTimeProgressbar;
	class UTextBlock* BuildingTimeTextBlock;
};
