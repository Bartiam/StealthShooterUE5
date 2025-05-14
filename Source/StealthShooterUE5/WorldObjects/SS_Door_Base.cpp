// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Door_Base.h"

ASS_Door_Base::ASS_Door_Base()
{
	// Create door frame and attach it to root component
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Frame"));
	DoorFrame->SetupAttachment(RootComponent);
}

void ASS_Door_Base::BeginPlay()
{
	Super::BeginPlay();

	BindCurveToTimeline(OpenDoorCurve, TimelineToOpenDoor);
}

void ASS_Door_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Promotes the timeline
	TimelineToOpenDoor.TickTimeline(DeltaTime);
}

void ASS_Door_Base::OpenDoor(float Value) {}

void ASS_Door_Base::BindCurveToTimeline(UCurveFloat* CurrentCurve, FTimeline& CurrentTimeline)
{
	// Checking that curve != nullptr
	if (CurrentCurve)
	{
		// Binds timeline to function
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ThisClass::OpenDoor);
		// Add curve to timeline
		CurrentTimeline.AddInterpFloat(CurrentCurve, TimelineProgress);
	}
}