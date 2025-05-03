// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSimpleDoor_Base.h"

#include "Net/UnrealNetwork.h"
#include "Components/BoxComponent.h"

// Sets default values
ASSSimpleDoor_Base::ASSSimpleDoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup base specifications of Platband
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Platband"));
	SetRootComponent(DoorFrame);
	DoorFrame->SetCollisionProfileName("BlockAll");

	// Setup base specifications of door
	Door = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door"));
	Door->SetupAttachment(DoorFrame);
	Door->SetCollisionProfileName(FName("BlockAll"));

	// Setup base specifications of overlap box collision
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(FName("Overlap Box"));
	OverlapBox->SetupAttachment(DoorFrame);
	OverlapBox->SetCollisionProfileName(FName("OverlapAll"));
 
	NetDormancy = DORM_DormantAll;
	NetUpdateFrequency = 30.f;
	SetReplicates(true);
	bReplicates = true;
}

void ASSSimpleDoor_Base::Interactable_Implementation()
{
	if (TimelineToOpenDoor.IsPlaying() || TimelineToOpenDoor.IsReversing()) return;

	if (HasAuthority())
	{
		if (bIsDoorClosed)
		{
			TimelineToOpenDoor.Play();
		}
		else
		{
			TimelineToOpenDoor.Reverse();
		}

		bIsDoorClosed = !bIsDoorClosed;
	}
}

void ASSSimpleDoor_Base::Multicast_OpenDoor_Implementation(float Value)
{
	FRotator CurrentDoorRotation = FRotator(0.f, DoorRotateAngle * Value, 0.f);
	Door->SetRelativeRotation(CurrentDoorRotation);
}

void ASSSimpleDoor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimelineToOpenDoor.TickTimeline(DeltaTime);
}

void ASSSimpleDoor_Base::BeginPlay()
{
	Super::BeginPlay();

	if (DoorCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ThisClass::Multicast_OpenDoor);
		TimelineToOpenDoor.AddInterpFloat(DoorCurve, TimelineProgress);
	}
}