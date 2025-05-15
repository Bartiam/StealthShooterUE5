// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ImportantRoomsDoor_Base.h"



// Sets default values
ASS_ImportantRoomsDoor_Base::ASS_ImportantRoomsDoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create piston and attch it to door frame
	Piston = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piston"));
	Piston->SetupAttachment(DoorFrame);

	// Create door and attach it to Piston
	Door = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door"));
	Door->SetupAttachment(Piston);

	// Attach Object Circled to Door
	ObjectCircled->SetupAttachment(Piston);
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

void ASS_ImportantRoomsDoor_Base::InteractableRelease_Implementation(const AActor* Interactor)
{
	// Checking that the object is currently running 
	if (TimelineToOpenDoor.IsPlaying() || TimelineToOpenDoor.IsReversing() ||
		TimelineToRotateLock.IsPlaying() || TimelineToRotateLock.IsReversing()) return;

	if (bIsDoorLock)
	{
		
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
			// Reverse play timeline
			TimelineToOpenDoor.Reverse();
		}

		bIsDoorClosed = !bIsDoorClosed;
	}
}

void ASS_ImportantRoomsDoor_Base::OpenDoor(float Value)
{
	FVector NewLocation = FMath::Lerp(LocationToLockDoor, LocationToOpenDoor, Value);
	Piston->SetRelativeLocation(NewLocation);
}

void ASS_ImportantRoomsDoor_Base::OpenLock(float Value)
{
	// Set new rotation for lock
	FRotator NewDoorRotation = FMath::Lerp(StartRotationLock, EndRotationLock, Value);
	ObjectCircled->SetRelativeRotation(NewDoorRotation);
}

