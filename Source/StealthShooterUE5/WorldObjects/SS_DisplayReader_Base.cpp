﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_DisplayReader_Base.h"
#include "Components/WidgetComponent.h"
#include "../UserInterface/SS_CardReaderWidget_Base.h"
#include "../WorldObjects/SS_ImportantRoomsDoor_Base.h"



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
	DisplayWidget_Component->SetRelativeScale3D(FVector(0.34f, 0.34f, 0.34f));
}



void ASS_DisplayReader_Base::BeginPlay()
{
	Super::BeginPlay();

	DisplayWidget_Pointer = CreateWidget<USS_CardReaderWidget_Base>(GetWorld(), DisplayWidget_Component->GetWidgetClass());

	if (GetParentActor())
	{
		CurrentDoor = Cast<ASS_Door_Base>(GetParentActor());

		DisplayWidget_Pointer->SetBrushColorToOpenDoor(CurrentDoor->GetIsDoorLock());
		DisplayWidget_Component->RequestRedraw();
	}

	SetCurrentSpecificationsToReader();

	DisplayWidget_Component->SetWidget(DisplayWidget_Pointer);
	DisplayWidget_Pointer->OwnerCodeReader = this;
}



void ASS_DisplayReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (TimerToIncorrectKey.IsValid()) return;

	if (CurrentDoor->GetIsDoorLock())
	{
		// Bint to inventory
		CurrentDoor->OpenAndBindToPlayerInventory(Interactor);

		DisplayWidget_Component->SetManuallyRedraw(false);

		CurrentDoor->OnTryToOpenDoor.AddDynamic(this, &ThisClass::PlayActionsWhenTryedDoorOpen);
	}
	else
	{
		CurrentDoor->InteractableRelease_Implementation(Interactor);
	}
}



void ASS_DisplayReader_Base::SetCurrentSpecificationsToReader()
{
	DisplayWidget_Component->SetManuallyRedraw(true);
	DisplayWidget_Component->SetRedrawTime(0.f);

	DisplayWidget_Pointer->SetBrushColorToOpenDoor(CurrentDoor->GetIsDoorLock());
	DisplayWidget_Component->RequestRedraw();

	GetWorldTimerManager().ClearTimer(TimerToIncorrectKey);
}



void ASS_DisplayReader_Base::PlayActionsWhenTryedDoorOpen()
{
	if (CurrentDoor->GetIsDoorLock())
	{
		// Noisy
		DisplayWidget_Pointer->ShowMessageEntry();

		GetWorldTimerManager().SetTimer(TimerToIncorrectKey, [this]()
			{
				SetCurrentSpecificationsToReader();
			},
			1.5f,
			false);
	}
	else
	{
		SetCurrentSpecificationsToReader();
	}

	CurrentDoor->OppositeReader->SetCurrentSpecificationsToReader();
	CurrentDoor->OnTryToOpenDoor.RemoveAll(this);
}
