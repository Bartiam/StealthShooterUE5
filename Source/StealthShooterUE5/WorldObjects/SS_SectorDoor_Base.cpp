// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_SectorDoor_Base.h"
#include "Components/WidgetComponent.h"



ASS_SectorDoor_Base::ASS_SectorDoor_Base()
{
	DoorFrame->SetRelativeScale3D(FVector(1.25f, 1.25f, 1.25f));

	ObjectCircled->SetupAttachment(DoorFrame);
	SecondObjectCircled->SetupAttachment(DoorFrame);

	InteractionWidget->SetupAttachment(DoorFrame);
}



void ASS_SectorDoor_Base::BeginPlay()
{
	Super::BeginPlay();

	GetReaderFromChildActors();

	// Checking when the door is locked for key and door is not closed 
	if (bIsDoorLock)
	{
		bIsDoorClosed = true;
	}
	else
	{
		if (!bIsDoorClosed)
		{
			ObjectCircled->SetRelativeLocation(LocationToOpenDoor * (-1));
			SecondObjectCircled->SetRelativeLocation(LocationToOpenDoor);
		}
	}
}



void ASS_SectorDoor_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (TimelineToOpenDoor.IsPlaying() || TimelineToOpenDoor.IsReversing()) return;

	if (bIsDoorLock)
	{
		SetTextInTheUIDuringTheGame(Interactor, TextWhenDoorIsLocked);
	}
	else
	{
		if (bIsDoorClosed)
		{
			// Play timeline 
			TimelineToOpenDoor.PlayFromStart();
		}
		else
		{
			// Reverse timeline
			TimelineToOpenDoor.ReverseFromEnd();
		}

		bIsDoorClosed = !bIsDoorClosed;
	}
}



void ASS_SectorDoor_Base::OpenDoor(float Value)
{
	// Set new location for left door
	FVector NewLocationLeftDoor = FMath::Lerp(LocationToLockDoor, LocationToOpenDoor, Value);
	SecondObjectCircled->SetRelativeLocation(NewLocationLeftDoor);

	// Set new location for right door
	FVector NewLocationRightDoor = FMath::Lerp(LocationToLockDoor, LocationToOpenDoor, Value * (-1));
	ObjectCircled->SetRelativeLocation(NewLocationRightDoor);
}



void ASS_SectorDoor_Base::TryToOpenDoor(FPickUpItemInfo ItemInfo, AActor* Interactor)
{
	if (ItemInfo.KeyPepmission.CodeToOpenDoor == DoorKeyPermission.CodeToOpenDoor)
	{
		SetIsDoorLock(false);
		InteractableRelease_Implementation(Interactor);
	}
	else
	{
		SetTextInTheUIDuringTheGame(Interactor, TextWhenSelectedIncorrectKey);
		SetIsDoorLock(true);
	}
}