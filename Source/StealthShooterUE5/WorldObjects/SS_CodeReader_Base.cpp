// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CodeReader_Base.h"
#include "SS_Door_Base.h"
#include "../Controllers/SSPlayerController_Base.h"
#include "../Core_C/SSHUD_Base.h"
#include "../UserInterface/SS_DuringTheGame_Base.h"
#include "../UserInterface/SS_CardReaderWidget_Base.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"



ASS_CodeReader_Base::ASS_CodeReader_Base()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);
}



void ASS_CodeReader_Base::BeginPlay()
{
	Super::BeginPlay();

	
}



void ASS_CodeReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (TimerToIncorrectKey.IsValid()) return;

	if (CurrentDoor->GetIsDoorLock())
	{
		CurrentPlayerController = ICharacterInterface::Execute_GetOwnerCharacterController(Interactor);
		CurrentPlayerController->SetControllerCodeReaderMode(this);

		SetCodeReaderEntryMode();
	}
	else
	{
		CurrentDoor->InteractableRelease_Implementation(Interactor);
	}
}



void ASS_CodeReader_Base::SetCodeReaderEntryMode()
{
	ObjectCircled->SetCollisionProfileName(FName("NoCollision"));
	DisplayWidget_Component->SetCollisionProfileName("BlockAll");

	DisplayWidget_Component->SetManuallyRedraw(false);
	DisplayWidget_Component->SetRedrawTime(0.f);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			DisplayWidget_Pointer->CodeEntryActivated();
		}, 
		1.f,
		false);

}



void ASS_CodeReader_Base::SetCodeReaderStaticMode()
{
	ObjectCircled->SetCollisionProfileName(FName("BlockAll"));
	DisplayWidget_Component->SetCollisionProfileName("NoCollision");

	DisplayWidget_Pointer->CodeEntryDeactivated();
}



void ASS_CodeReader_Base::BindOnCodeEntred(FName EntredCode, AActor* Interactor)
{
	//if (!CurrentDoor->TryToOpenDoorWhenItsLocked(EntredCode, Interactor))
	{
		// Noisy
		DisplayWidget_Pointer->ShowMessageEntry();
		
		GetWorldTimerManager().SetTimer(TimerToIncorrectKey, [this]()
			{
				SetSpecificationsToReader();
			},
			1.5f,
			false);
	}
	//else
	{
		DisplayWidget_Pointer->SetBrushColorToOpenDoor(CurrentDoor->GetIsDoorLock());
		OnCodeEntred.RemoveAll(this);
	}

	CurrentPlayerController->SetControllerBaseMode();
	SetCodeReaderStaticMode();
}
