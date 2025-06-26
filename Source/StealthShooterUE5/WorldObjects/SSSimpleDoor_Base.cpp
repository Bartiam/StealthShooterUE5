// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSimpleDoor_Base.h"
#include "../GAS/SS_AbilitySystemComponent.h"
#include "../Characters/SSCharacter_Base.h"



// Sets default values
ASSSimpleDoor_Base::ASSSimpleDoor_Base()
{
	// Attach object circled to Door Frame
	ObjectCircled->SetupAttachment(DoorFrame);
}



void ASSSimpleDoor_Base::TryToOpenDoor(FPickUpItemInfo ItemInfo, AActor* Interactor)
{
	Super::TryToOpenDoor(ItemInfo, Interactor);

	if (ItemInfo.KeyPepmission.PhysKeyType == DoorKeyPermission.PhysKeyType)
	{
		SetIsDoorLock(false);

		FTimerHandle TimerToOpenDoor;
		GetWorldTimerManager().SetTimer(TimerToOpenDoor, [this, Interactor] () 
			{
				// Opening door with a key sound
				InteractableRelease_Implementation(Interactor);
			}, 
			0.4f, 
			false);
	}
	else
	{
		SetTextInTheUIDuringTheGame(Interactor, TextWhenSelectedIncorrectKey);
		SetIsDoorLock(true);
	}
}



void ASSSimpleDoor_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	// Checking that the object is currently running 
	if (TimelineToOpenDoor.IsPlaying() || TimelineToOpenDoor.IsReversing() ||
		TimelineToOpenDoor_Lock.IsPlaying() || TimelineToOpenDoor_Lock.IsReversing()) return;

	if (bIsDoorLock)
	{
		SetTextInTheUIDuringTheGame(Interactor, TextWhenDoorIsLocked);

		if (LockDoorCurve)
		{
			EndRotationDoor = OpenedDoorRotationLocked;
			// Play timeline 
			TimelineToOpenDoor_Lock.PlayFromStart();
		}

		OpenAndBindToPlayerInventory(Interactor);
	}
	else
	{
		EndRotationDoor = OpenedDoorRotation;

		if (bIsDoorClosed)
		{
			// Play timeline 
			TimelineToOpenDoor.PlayFromStart();
		}
		else
		{
			// Reverse play timeline
			TimelineToOpenDoor.ReverseFromEnd();
		}

		bIsDoorClosed = !bIsDoorClosed;
	}
}



void ASSSimpleDoor_Base::OpenDoor(float Value)
{
	// Set new rotation for this object
	FRotator CurrentDoorRotation = FMath::Lerp(StartRotationDoor, EndRotationDoor, Value);
	ObjectCircled->SetRelativeRotation(CurrentDoorRotation);
}



void ASSSimpleDoor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Promotes the timeline
	TimelineToOpenDoor_Lock.TickTimeline(DeltaTime);
}



void ASSSimpleDoor_Base::BeginPlay()
{
	Super::BeginPlay();

	BindCurveToTimeline(LockDoorCurve, TimelineToOpenDoor_Lock);

	// Checking when the door is locked for key and door is not closed
	if (bIsDoorLock)
	{
		bIsDoorClosed = true;
	}
	else
	{
		if (!bIsDoorClosed)
		{
			ObjectCircled->SetRelativeRotation(OpenedDoorRotation);
		}
	}
}
