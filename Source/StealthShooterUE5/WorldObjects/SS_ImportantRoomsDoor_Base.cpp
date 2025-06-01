// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ImportantRoomsDoor_Base.h"



// Sets default values
ASS_ImportantRoomsDoor_Base::ASS_ImportantRoomsDoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Piston and attch it to door frame
	Piston = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piston"));
	Piston->SetupAttachment(DoorFrame);

	// Create Door Light and attach it to Door Frame
	DoorLight = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Light"));
	DoorLight->SetupAttachment(DoorFrame);

	// Attach Object Circled to Door
	ObjectCircled->SetupAttachment(Piston);

	// Create Door and attach it to Piston
	Lock = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door"));
	Lock->SetupAttachment(ObjectCircled);
	Lock->SetCollisionProfileName(FName("NoCollision"));
}

void ASS_ImportantRoomsDoor_Base::SetMaterialToLightDoor(UMaterial* NewColor)
{
	DoorLight->SetMaterial(1, NewColor);
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
		if (Interactor->Implements<UCharacterInterface>())
		{
			UpdateTextWhenDoorIsLocked(Interactor);
		}
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

ESSCardTypes ASS_ImportantRoomsDoor_Base::GetNeededCard() const
{ return NeededCard; }

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
	Lock->SetRelativeRotation(NewLockRotation);

	if (TimelineToRotateLock.GetPlaybackPosition() >= 2.f)
		TimelineToOpenDoor.Play();	
}

