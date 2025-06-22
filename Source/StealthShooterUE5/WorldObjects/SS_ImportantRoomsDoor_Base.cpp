// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ImportantRoomsDoor_Base.h"



// Sets default values
ASS_ImportantRoomsDoor_Base::ASS_ImportantRoomsDoor_Base()
{
	DoorFrame->SetRelativeScale3D(FVector(1.25f, 1.25f, 1.25f));

	// Create Piston and attch it to door frame
	Piston = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piston"));
	Piston->SetupAttachment(DoorFrame);

	// Create Door Light and attach it to Door Frame
	DoorLight = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Light"));
	DoorLight->SetupAttachment(DoorFrame);

	// Attach Object Circled to Door
	ObjectCircled->SetupAttachment(Piston);
	SecondObjectCircled->SetupAttachment(Piston);
}



void ASS_ImportantRoomsDoor_Base::TryToOpenDoor(FPickUpItemInfo ItemInfo, AActor* Interactor)
{
	Super::TryToOpenDoor(ItemInfo, Interactor);

	if (ItemInfo.KeyPepmission.CardType == DoorKeyPermission.CardType || ItemInfo.KeyPepmission.CardType == ESSCardType::Master_Card)
	{
		SetIsDoorLock(false);
		// Opening door with a key sound
		PlayChangesWhenDoorStateChanged();
		InteractableRelease_Implementation(Interactor);
	}
	else
	{
		SetTextInTheUIDuringTheGame(Interactor, TextWhenSelectedIncorrectKey);
		SetIsDoorLock(true);
	}
}



void ASS_ImportantRoomsDoor_Base::PlayChangesWhenDoorStateChanged()
{
	if (bIsDoorLock)
	{
		DoorLight->SetMaterial(1, LockDoorMaterial);
	}
	else
	{
		DoorLight->SetMaterial(1, OpenDoorMaterial);
	}
}



void ASS_ImportantRoomsDoor_Base::BeginPlay()
{
	Super::BeginPlay();

	if (CurveRotateLock)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ThisClass::OpenLock);
		TimelineToRotateLock.AddInterpFloat(CurveRotateLock, TimelineProgress);
	}

	PlayChangesWhenDoorStateChanged();
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
			Piston->SetRelativeLocation(LocationToOpenDoor);
			SecondObjectCircled->SetRelativeRotation(EndRotationLock);

			TimelineToRotateLock.SetPlaybackPosition(2.5f, false);
			TimelineToOpenDoor.SetPlaybackPosition(3.f, false);
		}
	}
}



void ASS_ImportantRoomsDoor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimelineToRotateLock.TickTimeline(DeltaTime);
}



void ASS_ImportantRoomsDoor_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	// Checking that the object is currently running 
	if (TimelineToOpenDoor.IsPlaying() || TimelineToOpenDoor.IsReversing() ||
		TimelineToRotateLock.IsPlaying() || TimelineToRotateLock.IsReversing()) return;

	if (bIsDoorLock)
	{
		SetTextInTheUIDuringTheGame(Interactor, TextWhenDoorIsLocked);
	}
	else
	{
		if (bIsDoorClosed)
		{
			// Play timeline 
			TimelineToRotateLock.Play();
		}
		else
		{
			// Reverse play timeline
			TimelineToOpenDoor.Reverse();
		}

		bIsDoorClosed = !bIsDoorClosed;
	}
}



void ASS_ImportantRoomsDoor_Base::OpenDoor(float Value)
{
	// Set new location for door
	FVector NewLocation = FMath::Lerp(LocationToLockDoor, LocationToOpenDoor, Value);
	Piston->SetRelativeLocation(NewLocation);

	if (TimelineToOpenDoor.GetPlaybackPosition() <= 0.f)
		TimelineToRotateLock.Reverse();
}



void ASS_ImportantRoomsDoor_Base::OpenLock(float Value)
{
	// Set new rotation for lock
	FRotator NewLockRotation = FMath::Lerp(StartRotationLock, EndRotationLock, Value);
	SecondObjectCircled->SetRelativeRotation(NewLockRotation);

	if (TimelineToRotateLock.GetPlaybackPosition() >= 2.5f)
		TimelineToOpenDoor.Play();
}

