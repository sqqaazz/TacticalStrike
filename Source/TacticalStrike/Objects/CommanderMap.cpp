// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderMap.h"
#include "Components/BoxComponent.h"
#include "GameMode/TacticalStrikeGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AIController/CommanderAI.h"
#include "Characters/CommanderUnit.h"
#include "Components/UnitsArray.h"
#include "Characters/Units/DefaultUnit/DefaultUnit.h"
#include "Engine/Font.h"
#include "DrawDebugHelpers.h"
#include "GameMode/TacticalStrikeGameInstance.h"

// Sets default values
ACommanderMap::ACommanderMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CommanderMapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CommanderMapMesh"));
	CommanderMapPlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CommanderMapPlaneMesh"));

	UnitCount_OneTime = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh_OneTime"));
	UnitCount_FiveTimes = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh_FiveTimes"));
	UnitCount_TwentyTimes = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh_TwentyTimes"));

	ResourcePlace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_ResourcePlace"));
	TechPlace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_TechPlace"));
	BuildingPlace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_BuildingPlace"));

	//UnitCountRender_OneTime = CreateDefaultSubobject<UTextRenderComponent>(TEXT("UnitTextRender_OneTime"));
	//UnitCountRender_FiveTimes = CreateDefaultSubobject<UTextRenderComponent>(TEXT("UnitTextRender_FiveTimes"));
	//UnitCountRender_TwentyTimes = CreateDefaultSubobject<UTextRenderComponent>(TEXT("UnitTextRender_TwentyTimes"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CommanderMap_Mesh(TEXT("StaticMesh'/Game/3DModels/StaticMesh/CommanderMap2.CommanderMap2'"));
	if (CommanderMap_Mesh.Succeeded())
	{
		CommanderMapMesh->SetStaticMesh(CommanderMap_Mesh.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CommanderMap_PlaneMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (CommanderMap_PlaneMesh.Succeeded())
	{
		CommanderMapPlaneMesh->SetStaticMesh(CommanderMap_PlaneMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> OneTimeMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (OneTimeMesh.Succeeded())
		UnitCount_OneTime->SetStaticMesh(OneTimeMesh.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FiveTimesMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (FiveTimesMesh.Succeeded())
		UnitCount_FiveTimes->SetStaticMesh(FiveTimesMesh.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TwentyTimesMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (TwentyTimesMesh.Succeeded())
		UnitCount_TwentyTimes->SetStaticMesh(TwentyTimesMesh.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ResourcePlaceMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (ResourcePlaceMesh.Succeeded())
		ResourcePlace->SetStaticMesh(ResourcePlaceMesh.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TechPlaceMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (TechPlaceMesh.Succeeded())
		TechPlace->SetStaticMesh(TechPlaceMesh.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingPlaceMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (BuildingPlaceMesh.Succeeded())
		BuildingPlace->SetStaticMesh(BuildingPlaceMesh.Object);

	//UFont* RenderFont = LoadObject<UFont>(nullptr, TEXT("Font'/Game/Font/kenvector_future_Font.kenvector_future_Font'"));
	//if (RenderFont)
	//{
	//	UnitCountRender_OneTime->SetFont(RenderFont);
	//	UnitCountRender_FiveTimes->SetFont(RenderFont);
	//	UnitCountRender_TwentyTimes->SetFont(RenderFont);
	//}

	//UnitCountRender_OneTime->SetTextRenderColor(FColor::Black);
	//UnitCountRender_FiveTimes->SetTextRenderColor(FColor::Black);
	//UnitCountRender_TwentyTimes->SetTextRenderColor(FColor::Black);
	//UnitCountRender_OneTime->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
	//UnitCountRender_FiveTimes->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
	//UnitCountRender_TwentyTimes->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));

	//static ConstructorHelpers::FObjectFinder<UFont> RenderFont(TEXT("Font'/Game/Font/kenvector_future_Font.kenvector_future_Font'"));
	//if (RenderFont.Succeeded())
	//{
	//	UnitCountRender_OneTime->SetFont(RenderFont.Object);
	//	UnitCountRender_FiveTimes->SetFont(RenderFont.Object);
	//	UnitCountRender_TwentyTimes->SetFont(RenderFont.Object);
	//	UnitCountRender_OneTime->SetTextRenderColor(FColor::Black);
	//	UnitCountRender_FiveTimes->SetTextRenderColor(FColor::Black);
	//	UnitCountRender_TwentyTimes->SetTextRenderColor(FColor::Black);
	//	UnitCountRender_OneTime->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
	//	UnitCountRender_FiveTimes->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
	//	UnitCountRender_TwentyTimes->SetWorldScale3D(FVector(30.0f, 30.0f, 30.0f));
	//	UnitCountRender_OneTime->SetWorldSize(5.0f);
	//	UnitCountRender_FiveTimes->SetWorldSize(5.0f);
	//	UnitCountRender_TwentyTimes->SetWorldSize(5.0f);
	//}

	//UnitCountRender_OneTime->Text = FText::FromString("1x");
	//UnitCountRender_FiveTimes->Text = FText::FromString("5x");
	//UnitCountRender_TwentyTimes->Text = FText::FromString("20x");


	//static ConstructorHelpers::FClassFinder<ARifleMan> RifleMan_Spawn(TEXT("Blueprint'/Game/Blueprints/Count/BP_RifleMan_Count.BP_RifleMan_Count_C'"));
	//if (RifleMan_Spawn.Succeeded())
	//	SpawnRifleMan = RifleMan_Spawn.Class;
	//static ConstructorHelpers::FClassFinder<ASwordMan> SwordMan_Spawn(TEXT("Blueprint'/Game/Blueprints/Count/BP_SwordMan_Count.BP_SwordMan_Count_C'"));
	//if (SwordMan_Spawn.Succeeded())
	//	SpawnSwordMan = SwordMan_Spawn.Class;
	//static ConstructorHelpers::FClassFinder<AMutant> Mutant_Spawn(TEXT("Blueprint'/Game/Blueprints/Count/BP_Mutant_Count.BP_Mutant_Count_C'"));
	//if (Mutant_Spawn.Succeeded())
	//	SpawnMutant = Mutant_Spawn.Class;



	UnitCount_OneTime->SetCollisionProfileName(TEXT("NoCollision"));
	UnitCount_FiveTimes->SetCollisionProfileName(TEXT("NoCollision"));
	UnitCount_TwentyTimes->SetCollisionProfileName(TEXT("NoCollision"));

	RootComponent = CommanderMapMesh;
	CommanderMapPlaneMesh->SetupAttachment(RootComponent);
	UnitCount_OneTime->SetupAttachment(RootComponent);
	UnitCount_FiveTimes->SetupAttachment(RootComponent);
	UnitCount_TwentyTimes->SetupAttachment(RootComponent);

	ResourcePlace->SetupAttachment(RootComponent);
	TechPlace->SetupAttachment(RootComponent);
	BuildingPlace->SetupAttachment(RootComponent);

	//UnitCountRender_OneTime->SetupAttachment(RootComponent);
	//UnitCountRender_FiveTimes->SetupAttachment(RootComponent);
	//UnitCountRender_TwentyTimes->SetupAttachment(RootComponent);

	UnitsClass = UUnitsArray::StaticClass();

	CommanderMapPlaneMesh->SetRelativeLocation(FVector(-3000.0f, 0.0f, 0.0f));
	CommanderMapPlaneMesh->SetRelativeScale3D(FVector(25.0f, 52.0f, 1.0f));

	UnitCount_OneTime->SetRelativeLocation(FVector(-1100.0f, 1100.0f, 500.0f));
	UnitCount_FiveTimes->SetRelativeLocation(FVector(-1100.0f, -850.0f, 500.0f));
	UnitCount_TwentyTimes->SetRelativeLocation(FVector(-1100.0f, -2850.0f, 500.0f));

	ResourcePlace->SetRelativeLocation(FVector(4000.0f, -3000.0f, 500.0f));
	TechPlace->SetRelativeLocation(FVector(4000.0f, 1000.0f, 500.0f));
	BuildingPlace->SetRelativeLocation(FVector(2500.0f, -3000.0f, 500.0f));
}

// Called when the game starts or when spawned
void ACommanderMap::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UTacticalStrikeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	UnitCount_OneTime->SetRelativeLocation(FVector(-1100.0f, 1100.0f, 500.0f));
	UnitCount_FiveTimes->SetRelativeLocation(FVector(-1100.0f, -850.0f, 500.0f));
	UnitCount_TwentyTimes->SetRelativeLocation(FVector(-1100.0f, -2850.0f, 500.0f));

	ResourcePlace->SetRelativeLocation(FVector(4000.0f, -3000.0f, 500.0f));
	TechPlace->SetRelativeLocation(FVector(4000.0f, 1000.0f, 500.0f));
	BuildingPlace->SetRelativeLocation(FVector(2500.0f, -3000.0f, 500.0f));

	//UnitCountRender_OneTime->SetRelativeLocation(FVector(-1100.0f, 1100.0f, 500.0f));
	//UnitCountRender_FiveTimes->SetRelativeLocation(FVector(-1100.0f, -850.0f, 500.0f));
	//UnitCountRender_TwentyTimes->SetRelativeLocation(FVector(-1100.0f, -2850.0f, 500.0f));

	BlueTeamSpawnVector = UnitCount_OneTime->GetComponentLocation() + FVector(-700.0f, 400.0f, -200.0f);
	RedTeamSpawnVector = UnitCount_OneTime->GetComponentLocation() + FVector(700.0f, -400.0f, -200.0f);

	//AI 컨트롤러 가져옴
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACommanderUnit::StaticClass(), CommanderUnitArray);
	if (CommanderUnitArray[0]->ActorHasTag("CommanderAI"))
		CommanderAI = Cast<ACommanderAI>(Cast<APawn>(CommanderUnitArray[0])->GetController());
	else if (CommanderUnitArray[1]->ActorHasTag("CommanderAI"))
		CommanderAI = Cast<ACommanderAI>(Cast<APawn>(CommanderUnitArray[1])->GetController());

	if (CommanderAI != nullptr)
		CommanderAI->AIBuildingSpawnDelegate.AddDynamic(this, &ACommanderMap::BuildingSpawn);

	SpawnBlueUnit = GetWorld() != NULL ? GetWorld()->GetGameState<ATacticalStrikeGameStateBase>() : NULL;
	if (SpawnBlueUnit != nullptr)
		SpawnBlueUnit->WorldUnitSpawnTrigger.AddDynamic(this, &ACommanderMap::CheckUnitCount);
	
}
/*
// Called every frame
void ACommanderMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

void ACommanderMap::CheckUnitCount()
{
	//배열 초기화
	UnitsArray.Empty();
	//배열에 들어갈 객체 인스턴스화
	//auto UnitsInfo = NewObject<UUnitsArray>(UnitsClass);

	//유닛이 있는 곳의 트레이스 위치와 크기
	if (this->ActorHasTag("RedTeamMap"))
	{
		UnitCount_OneTime_Location = UnitCount_OneTime->GetComponentLocation() + FVector(1400.0f, -800.0f, -250.0f);
		UnitCount_FiveTimes_Location = UnitCount_FiveTimes->GetComponentLocation() + FVector(1400.0f, -800.0f, -250.0f);
		UnitCount_TwentyTimes_Location = UnitCount_TwentyTimes->GetComponentLocation() + FVector(1400.0f, -800.0f, -250.0f);
	}
	else if (this->ActorHasTag("BlueTeamMap"))
	{
		UnitCount_OneTime_Location = UnitCount_OneTime->GetComponentLocation() + FVector(-1400.0f, 800.0f, -200.0f);
		UnitCount_FiveTimes_Location = UnitCount_FiveTimes->GetComponentLocation() + FVector(-1400.0f, 800.0f, -200.0f);
		UnitCount_TwentyTimes_Location = UnitCount_TwentyTimes->GetComponentLocation() + FVector(-1400.0f, 800.0f, -200.0f);
	}
	FVector UnitCount_Scale = FVector(1400.0f, 800.0f, 200.0f);

	//트레이스에 판정된 유닛들을 담을 배열
	TArray<FOverlapResult> OverlapResults_OneTime;
	TArray<FOverlapResult> OverlapResults_FiveTimes;
	TArray<FOverlapResult> OverlapResults_TwentyTimes;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);

	//일정 범위 안에 있는 유닛들을 트레이스를 활용해 검출
	bool bResult_OneTime = GetWorld()->OverlapMultiByChannel(
		OverlapResults_OneTime,
		UnitCount_OneTime_Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeBox(UnitCount_Scale),
		CollisionQueryParam
	);
	bool bResult_FiveTimes = GetWorld()->OverlapMultiByChannel(
		OverlapResults_FiveTimes,
		UnitCount_FiveTimes_Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeBox(UnitCount_Scale),
		CollisionQueryParam
	);
	bool bResult_TwentyTimes = GetWorld()->OverlapMultiByChannel(
		OverlapResults_TwentyTimes,
		UnitCount_TwentyTimes_Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeBox(UnitCount_Scale),
		CollisionQueryParam
	);
	if (bResult_OneTime)
	{
		DrawDebugBox(GetWorld(), UnitCount_OneTime_Location, UnitCount_Scale, FColor::Green, false, 1.0f);
		AddUnitCount(OverlapResults_OneTime, 1);
	}
	else
	{
		DrawDebugBox(GetWorld(), UnitCount_OneTime_Location, UnitCount_Scale, FColor::Red, false, 1.0f);
	}
	
	if (bResult_FiveTimes)
	{
		DrawDebugBox(GetWorld(), UnitCount_FiveTimes_Location, UnitCount_Scale, FColor::Green, false, 1.0f);
		AddUnitCount(OverlapResults_FiveTimes, 5);
	}
	else
	{
		DrawDebugBox(GetWorld(), UnitCount_FiveTimes_Location, UnitCount_Scale, FColor::Red, false, 1.0f);
	}
	if (bResult_TwentyTimes)
	{
		DrawDebugBox(GetWorld(), UnitCount_TwentyTimes_Location, UnitCount_Scale, FColor::Green, false, 1.0f);
		AddUnitCount(OverlapResults_TwentyTimes, 20);
	}
	else
	{
		DrawDebugBox(GetWorld(), UnitCount_TwentyTimes_Location, UnitCount_Scale, FColor::Red, false, 1.0f);
	}
	UnitSpawnDelegate.Broadcast();
}

//건물에서 유닛 카운트 장소로 유닛 스폰 
void ACommanderMap::BuildingUnitSpawn(FString Team, uint8 UnitType)
{
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FVector SpawnUnitScale = CheckUnitSpawnScale(UnitType);
	if (ActorHasTag("BlueTeamMap") && Team == "Blue")
	{
		for (float i = BlueTeamSpawnVector.X; i > BlueTeamSpawnVector.X - 1400.0f; i -= 80.0f)
		{
			for (float j = BlueTeamSpawnVector.Y; j < BlueTeamSpawnVector.Y + 800.0f; j += 80.0f)
			{
				bool bResult = GetWorld()->OverlapMultiByChannel(
					OverlapResults,
					FVector(i, j, BlueTeamSpawnVector.Z),
					FQuat::Identity,
					ECollisionChannel::ECC_GameTraceChannel5,
					FCollisionShape::MakeBox(SpawnUnitScale),
					CollisionQueryParam
				);
				//UE_LOG(LogTemp, Log, TEXT("x: %f, y: %f, z: %f"), i, j, SpawnVector.Z);
				if (bResult)
				{
					DrawDebugBox(GetWorld(), FVector(i, j, BlueTeamSpawnVector.Z), SpawnUnitScale, FColor::Green, false, 1.0f);
					continue;
				}
				else
				{
					DrawDebugBox(GetWorld(), FVector(i, j, BlueTeamSpawnVector.Z), SpawnUnitScale, FColor::Red, false, 1.0f);
					//UE_LOG(LogTemp, Log, TEXT("SpawnLocation: %f, %f, %f"), i, j, SpawnVector.Z);
					CountPlaceSpawnDelegate.Broadcast(UnitType, FVector(i, j, BlueTeamSpawnVector.Z));
					return;
				}
			}
		}
	}
	else if (ActorHasTag("RedTeamMap") &&  Team == "Red")
	{
		for (float i = RedTeamSpawnVector.X; i > RedTeamSpawnVector.X - 1400.0f; i -= 80.0f)
		{
			for (float j = RedTeamSpawnVector.Y; j > RedTeamSpawnVector.Y - 800.0f; j -= 80.0f)
			{
				bool bResult = GetWorld()->OverlapMultiByChannel(
					OverlapResults,
					FVector(i, j, RedTeamSpawnVector.Z),
					FQuat::Identity,
					ECollisionChannel::ECC_GameTraceChannel5,
					FCollisionShape::MakeBox(SpawnUnitScale),
					CollisionQueryParam
				);
				//UE_LOG(LogTemp, Log, TEXT("x: %f, y: %f, z: %f"), i, j, SpawnVector.Z);
				if (bResult)
				{
					DrawDebugBox(GetWorld(), FVector(i, j, RedTeamSpawnVector.Z), SpawnUnitScale, FColor::Green, false, 1.0f);
					continue;
				}
				else
				{
					DrawDebugBox(GetWorld(), FVector(i, j, RedTeamSpawnVector.Z), SpawnUnitScale, FColor::Red, false, 1.0f);
					CountPlaceSpawnDelegate.Broadcast(UnitType, FVector(i, j, RedTeamSpawnVector.Z));
					//CountPlaceSpawnDelegate.Broadcast(UnitType);
					//SpawnUnit(UnitType, FVector(i, j, SpawnVector.Z));
					return;
				}
			}
		}
	}
}

//AI 건물 스폰
void ACommanderMap::BuildingSpawn(uint8 BuildingType)
{
	if (!ActorHasTag("RedTeamMap"))
		return;
	FVector AIBuildingSpawnLocation = BuildingPlace->GetComponentLocation();
	AIBuildingSpawnLocation.X += 1500.0f;
	AIBuildingSpawnLocation.Y += -1500.0f;
	AIBuildingSpawnLocation.Z += -275.0f;

	SpawnBuildingDelegate.Broadcast(BuildingType, AIBuildingSpawnLocation);
	
}

FVector ACommanderMap::CheckUnitSpawnScale(uint8 UnitType)
{
	if (UnitType == 1)
		return FVector(80.0f, 80.0f, 100.0f);
	else if (UnitType == 2)
		return FVector(80.0f, 80.0f, 100.0f);
	else if (UnitType == 3)
		return FVector(160.0f, 160.0f, 200.0f);
	else
		return FVector(0, 0, 0);
}

void ACommanderMap::AddUnitCount(TArray<FOverlapResult> TargetResultArray, uint8 AddCount)
{

	for (uint8 i = 0; i < TargetResultArray.Num(); i++)
	{
		//유닛 액터를 유닛번호로 교체
		uint8 UnitType = ConvertUnitType(TargetResultArray[i]);
		//UE_LOG(LogTemp, Log, TEXT("yp: %d"), UnitType);
			//배열에 들어갈 객체 인스턴스화
		UUnitsArray* UnitsInfo = NewObject<UUnitsArray>(UnitsClass);

		UnitsInfo->UnitType = UnitType;
		UnitsInfo->UnitCount = AddCount;
		//UE_LOG(LogTemp, Log, TEXT("Num: %d"), UnitsArray.Num());
		//유닛이 배열에 등록되어 있으면 갯수 증가, 없으면 배열에 새로 할당
		
		int32 Index = UnitsArray.IndexOfByPredicate([UnitType](UUnitsArray* Array) {
			return Array->UnitType == UnitType;
			});
		if (Index != -1)
		{
			UnitsArray[Index]->UnitCount += AddCount;
		}
		else
		{
			UnitsArray.Emplace(UnitsInfo);
		}
		
	}
}

//찾은 액터를 유닛 번호로 변경
uint8 ACommanderMap::ConvertUnitType(FOverlapResult TargetActor)
{
	ADefaultUnit* ConvertType = Cast<ADefaultUnit>(TargetActor.GetActor());
	if (ConvertType != nullptr)
		return ConvertType->UnitType;
	return 0;
	//FString UnitName = TargetActor.GetActor()->GetName();
	//if (UnitName.Contains("Rifle"))
	//	return 1;
	//else if (UnitName.Contains("Sword"))
	//	return 2;
	//else if (UnitName.Contains("Mutant"))
	//	return 3;
	//else
	//	return 0;
}