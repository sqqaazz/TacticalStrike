// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Buildings/DefaultBuilding.h"
#include "Building_GatheringResource.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALSTRIKE_API ABuilding_GatheringResource : public ADefaultBuilding
{
	GENERATED_BODY()
	
public:
	ABuilding_GatheringResource();

	//UPROPERTY()
	//TArray<class ABuilding_Crystal> RangeCrystalArr;

	void ChangeRangeCrystal();

	TArray<class ABuilding_Crystal*> GetRangeCrystal();
protected:
	virtual void BeginPlay() override;

	//virtual void SetBuildingScale() override;
	///void SetEnableMat() override;
	//void SetDisableMat() override;
	//void SetBasicMat() override;

	///void GetBuildingMaterial();

private:
	//UPROPERTY()
	//class AGridActor* GridActor;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* NiagaraComponent_Range;

	void SetNiagaraRange(float Range);

	UPROPERTY()
	float GatheringRange;

	TArray<class ABuilding_Crystal*> ChangeRangeCrystalMat();

	void ClearCrystalRange();

	UPROPERTY()
	TArray<class ABuilding_Crystal*> CurCrystalArr;
};
