// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandSlotsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ObjectTooltipWidget.h"
#include "DummyTooltipWidget.h"

UCommandSlotsWidget::UCommandSlotsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UObjectTooltipWidget> OBJECTTOOLTIPWIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/Widgets/BP_ObjectTooltipWidget.BP_ObjectTooltipWidget_C'"));
	if (OBJECTTOOLTIPWIDGET.Succeeded())
		ObjectTooltipWidgetClass = OBJECTTOOLTIPWIDGET.Class;
}

void UCommandSlotsWidget::SetObjectType(uint8 Type)
{
	UpdateTooltip(Type);
}
void UCommandSlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	

	BuildingBackgroundImage = Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage")));
	BuildingButton = Cast<UButton>(GetWidgetFromName(TEXT("SlotButton")));
	BuildingIconTexture = Cast<UImage>(GetWidgetFromName(TEXT("BuildingImage")));

	//BuildingButton->SetRenderOpacity(0.0f);
	BuildingBackgroundImage->SetVisibility(ESlateVisibility::Collapsed);
	
	ObjectTooltipWidget = Cast<UObjectTooltipWidget>(CreateWidget(GetWorld(), ObjectTooltipWidgetClass));
	this->SetToolTip(ObjectTooltipWidget);
}

void UCommandSlotsWidget::UpdateTooltip(uint8 Type)
{
	if (ObjectTooltipWidget != nullptr && BuildingButton != nullptr)
	{
		if (Type == 0)
			ObjectTooltipWidget->SetEmpty();
		else if (Type < 100)
			ObjectTooltipWidget->SetUnitTooltip(Type);
		else
			ObjectTooltipWidget->SetBuildingTooltip(Type);
	}
}

void UCommandSlotsWidget::SetSlotImageTexture2D(UTexture2D* TargetTexture)
{
	if (BuildingIconTexture != nullptr)
		BuildingIconTexture->SetBrushFromTexture(TargetTexture);
}

void UCommandSlotsWidget::SetSlotImageMat(UMaterial* TargetMaterial)
{
	if (BuildingIconTexture != nullptr)
		BuildingIconTexture->SetBrushFromMaterial(TargetMaterial);
}