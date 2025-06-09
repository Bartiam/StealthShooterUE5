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



void ASS_CodeReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (TimerToIncorrectKey.IsValid()) return;

	if (CurrentDoor->GetIsDoorLock())
	{
		DisplayWidget_Component->SetManuallyRedraw(false);

		if (Interactor->Implements<UCharacterInterface>())
			CurrentPlayerController = Cast<ASSPlayerController_Base>(ICharacterInterface::Execute_GetOwnerCharacterController(Interactor));

		CurrentDoor->OnTryToOpenDoor.AddDynamic(this, &ThisClass::PlayActionsWhenTryedDoorOpen);
		OnCodeEntred.AddDynamic(this, &ThisClass::BindToReciaveCode);

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

	CurrentPlayerController->SetControllerCodeReaderMode(this);
}



void ASS_CodeReader_Base::SetCodeReaderStaticMode()
{
	ObjectCircled->SetCollisionProfileName(FName("BlockAll"));
	DisplayWidget_Component->SetCollisionProfileName("NoCollision");

	DisplayWidget_Pointer->CodeEntryDeactivated();
	CurrentPlayerController->SetControllerBaseMode();
}

void ASS_CodeReader_Base::BindToReciaveCode(FName ReciavedCode, AActor* Interactor)
{
	FPickUpItemInfo ItemInfo;
	ItemInfo.KeyPepmission.CodeToOpenDoor = ReciavedCode;

	CurrentDoor->TryToOpenDoor(ItemInfo, Interactor);

	OnCodeEntred.RemoveAll(this);
}



void ASS_CodeReader_Base::PlayActionsWhenTryedDoorOpen()
{
	Super::PlayActionsWhenTryedDoorOpen();
	SetCodeReaderStaticMode();
	CurrentPlayerController = nullptr;
}
