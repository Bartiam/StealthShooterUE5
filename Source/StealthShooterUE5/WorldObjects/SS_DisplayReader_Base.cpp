// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_DisplayReader_Base.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"



ASS_DisplayReader_Base::ASS_DisplayReader_Base()
{
	// Create Display widget and set base specifications
	DisplayWidget_Component = CreateDefaultSubobject<UWidgetComponent>(FName("Display Widget"));
	DisplayWidget_Component->SetupAttachment(RootComponent);
	DisplayWidget_Component->SetCollisionProfileName(FName("NoCollision"));
	DisplayWidget_Component->SetWidgetSpace(EWidgetSpace::World);
	DisplayWidget_Component->SetRelativeLocation(FVector(12.f, 1.f, 35.f));
	DisplayWidget_Component->SetCastShadow(false);
	DisplayWidget_Component->SetBlendMode(EWidgetBlendMode::Transparent);
}



void ASS_DisplayReader_Base::BeginPlay()
{
	Super::BeginPlay();

	DisplayWidget_Pointer = CreateWidget<UUserWidget>(GetWorld(), DisplayWidget_Component->GetWidgetClass());
	DisplayWidget_Component->SetWidget(DisplayWidget_Pointer);
}