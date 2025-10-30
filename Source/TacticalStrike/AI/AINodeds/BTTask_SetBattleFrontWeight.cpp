// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetBattleFrontWeight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AIController/CommanderAI.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Objects/Tample/DefaultTample.h"

UBTTask_SetBattleFrontWeight::UBTTask_SetBattleFrontWeight()
{
	NodeName = TEXT("SetBattleFrontWeight");
	BattleFrontAvg = 0;
}

EBTNodeResult::Type UBTTask_SetBattleFrontWeight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACommanderAI* CommanderAI = Cast<ACommanderAI>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	if (CommanderAI != nullptr)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultUnit::StaticClass(), DefaultUnitArr);
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultTample::StaticClass(), TampleArr);
		if (DefaultUnitArr.Num() != 0)
		{
			for (int32 i = 0; i < DefaultUnitArr.Num(); i++)
			{
				if (DefaultUnitArr[i]->ActorHasTag("RedTeamUnit"))
				{
					ADefaultUnit* DefaultUnit = Cast<ADefaultUnit>(DefaultUnitArr[i]);
					if (DefaultUnit != nullptr)
						RedTeamUnitArr.Add(DefaultUnit);
				}
			}

			if (RedTeamUnitArr.Num() >= 2)
			{
				RedTeamUnitArr.Sort([](const ADefaultUnit& Result1, const ADefaultUnit& Result2) {
					return Result1.GetActorLocation().X < Result2.GetActorLocation().X;
				});
			}

			if (RedTeamUnitArr.Num() > 5)
			{
				for (int32 i = 0; i < 5; i++)
					BattleFrontAvg += DefaultUnitArr[i]->GetActorLocation().X;
				BattleFrontAvg /= 5;
			}
			else
			{
				for (int32 i = 0; i < DefaultUnitArr.Num(); i++)
					BattleFrontAvg += DefaultUnitArr[i]->GetActorLocation().X;
				BattleFrontAvg /= DefaultUnitArr.Num();
			}

		}
		//if (RedTeamUnitArr.Num() > 0)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("Num: %d, Location: %f"), RedTeamUnitArr.Num(), RedTeamUnitArr[0]->GetActorLocation().X);
		//}
		float RedTampleXPos;
		float BlueTampleXPos;

		if (TampleArr[0]->GetActorLocation().X < TampleArr[1]->GetActorLocation().X)
		{
			RedTampleXPos = TampleArr[1]->GetActorLocation().X;
			BlueTampleXPos = TampleArr[0]->GetActorLocation().X;
		}
		else
		{
			RedTampleXPos = TampleArr[0]->GetActorLocation().X;
			BlueTampleXPos = TampleArr[1]->GetActorLocation().X;
		}

		//가중치 높을수록 전선 밀림
		float BattleFrontWeight = FMath::Clamp((BattleFrontAvg - BlueTampleXPos) / (RedTampleXPos - BlueTampleXPos), 0.0f, 1.0f);
		
		

		/*float BattleFrontWeight = FMath::Lerp(TampleArr[0]->GetActorLocation().X, TampleArr[1]->GetActorLocation().X,
			(BattleFrontAvg - TampleArr[0]->GetActorLocation().X) / (TampleArr[1]->GetActorLocation().X - TampleArr[0]->GetActorLocation().X));*/
		if (BattleFrontWeight < 0.2f)
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BattleFrontWeightKey, 0.2f);
		else
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ACommanderAI::BattleFrontWeightKey, BattleFrontWeight);
		//UE_LOG(LogTemp, Log, TEXT("Weight: %f"), BattleFrontWeight);

		DefaultUnitArr.Empty();
		RedTeamUnitArr.Empty();
		BattleFrontAvg = 0;

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}