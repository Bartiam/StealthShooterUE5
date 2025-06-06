// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_SectorDoor_Base.h"

ASS_SectorDoor_Base::ASS_SectorDoor_Base()
{
	ObjectCircled->SetupAttachment(DoorFrame);
	SecondObjectCircled->SetupAttachment(DoorFrame);
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
			TimelineToOpenDoor.Play();
		}
		else
		{
			// Reverse timeline
			TimelineToOpenDoor.Reverse();
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