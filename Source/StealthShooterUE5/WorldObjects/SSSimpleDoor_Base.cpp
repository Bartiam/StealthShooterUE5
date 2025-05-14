// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSimpleDoor_Base.h"

// Sets default values
ASSSimpleDoor_Base::ASSSimpleDoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and setup base specifications of Platband
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Platband"));
	DoorFrame->SetupAttachment(RootComponent);

	ObjectCircled->SetupAttachment(DoorFrame);
}

void ASSSimpleDoor_Base::InteractableRelease_Implementation(const AActor* Interactor)
{
	// Checking that the object is currently running 
	if (TimelineToOpenDoor.IsPlaying() || TimelineToOpenDoor.IsReversing() ||
		TimelineToOpenDoor_Lock.IsPlaying() || TimelineToOpenDoor_Lock.IsReversing()) return;

	if (bIsDoorLock)
	{
		CurrentDoorRotateAngle = LockDoorRotateAngle;
		// Play timeline 
		TimelineToOpenDoor_Lock.PlayFromStart();
	}
	else
	{
		CurrentDoorRotateAngle = OpenDoorRotateAngle;

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

void ASSSimpleDoor_Base::OpenDoor(float Value)
{
	// Set new rotation for this object
	FRotator CurrentDoorRotation = FRotator(0.f, CurrentDoorRotateAngle * Value, 0.f);
	ObjectCircled->SetRelativeRotation(CurrentDoorRotation);
}

void ASSSimpleDoor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Promotes the timeline
	TimelineToOpenDoor.TickTimeline(DeltaTime);
	TimelineToOpenDoor_Lock.TickTimeline(DeltaTime);
}

void ASSSimpleDoor_Base::BeginPlay()
{
	Super::BeginPlay();

	// Checking that curve != nullptr
	if (OpenDoorCurve)
	{
		// Binds timeline to function
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ThisClass::OpenDoor);
		// Add curve to timeline
		TimelineToOpenDoor.AddInterpFloat(OpenDoorCurve, TimelineProgress);
	}
	// Checking that curve != nullptr
	if (LockDoorCurve)
	{
		// Binds timeline to function
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ThisClass::OpenDoor);
		// Add curve to timeline
		TimelineToOpenDoor_Lock.AddInterpFloat(LockDoorCurve, TimelineProgress);
	}
}