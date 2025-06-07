// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_DisplayReader_Base.h"
#include "Components/WidgetComponent.h"
#include "../UserInterface/SS_CardReaderWidget_Base.h"
#include "../WorldObjects/SS_Door_Base.h"



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
	DisplayWidget_Component->SetDrawSize(FVector2D(64.f, 64.f));
	DisplayWidget_Component->SetManuallyRedraw(true);
	DisplayWidget_Component->SetRedrawTime(1.f);
	DisplayWidget_Component->SetRelativeScale3D(FVector(0.34f, 0.34f, 0.34f));
}



void ASS_DisplayReader_Base::BeginPlay()
{
	Super::BeginPlay();

	DisplayWidget_Pointer = CreateWidget<USS_CardReaderWidget_Base>(GetWorld(), DisplayWidget_Component->GetWidgetClass());

	if (GetParentActor())
	{
		CurrentDoor = Cast<ASS_Door_Base>(GetParentActor());
		PlayChangesWhenDoorStateChanged();
		CurrentDoor->OnDoorStateChanged.AddDynamic(this, &ThisClass::PlayChangesWhenDoorStateChanged);
	}

	DisplayWidget_Component->SetWidget(DisplayWidget_Pointer);
	DisplayWidget_Pointer->OwnerCodeReader = this;
}



void ASS_DisplayReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (CurrentDoor->GetIsDoorLock())
	{
		CurrentDoor->OpenAndBindToPlayerInventory(Interactor);
	}
	else
	{
		CurrentDoor->InteractableRelease_Implementation(Interactor);
	}
}

void ASS_DisplayReader_Base::PlayChangesWhenDoorStateChanged()
{
	DisplayWidget_Pointer->SetBrushColorToOpenDoor(CurrentDoor->GetIsDoorLock());
	DisplayWidget_Component->RequestRedraw();
}
