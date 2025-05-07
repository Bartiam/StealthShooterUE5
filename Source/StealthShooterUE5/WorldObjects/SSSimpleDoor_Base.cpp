// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSimpleDoor_Base.h"

#include "Net/UnrealNetwork.h"

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

void ASSSimpleDoor_Base::Interactable_Implementation()
{
	// Checking that the object is currently running 
	if (TimelineToOpenDoor.IsPlaying() || TimelineToOpenDoor.IsReversing()) return;
	// Checking that this function is running on the server
	if (HasAuthority())
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

void ASSSimpleDoor_Base::Multicast_OpenDoor_Implementation(float Value)
{
	// Set new rotation for this object
	FRotator CurrentDoorRotation = FRotator(0.f, DoorRotateAngle * Value, 0.f);
	ObjectCircled->SetRelativeRotation(CurrentDoorRotation);
}

void ASSSimpleDoor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Promotes the timeline
	TimelineToOpenDoor.TickTimeline(DeltaTime);
}

void ASSSimpleDoor_Base::BeginPlay()
{
	Super::BeginPlay();

	// Checking that curve != nullptr
	if (DoorCurve)
	{
		// Binds timeline to function
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ThisClass::Multicast_OpenDoor);
		// Add curve to timeline
		TimelineToOpenDoor.AddInterpFloat(DoorCurve, TimelineProgress);
	}
}