// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Door_Base.h"
#include "../Core_C/SSHUD_Base.h"
#include "../Controllers/SSPlayerController_Base.h"
#include "../UserInterface/SS_DuringTheGame_Base.h"



ASS_Door_Base::ASS_Door_Base()
{
	// Create door frame and attach it to root component
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Frame"));
	DoorFrame->SetupAttachment(RootComponent);

	

	bIsCircledObject = false;
}



bool ASS_Door_Base::GetIsDoorLock() const
{ return bIsDoorLock; }



void ASS_Door_Base::SetIsDoorLock(const bool& NewValue)
{ bIsDoorLock = NewValue; }



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



void ASS_Door_Base::UpdateTextWhenDoorIsLocked(AActor* Interactor)
{
	auto CurrentHUD = ICharacterInterface::Execute_GetOwnerCharacterController(Interactor)->GetCurrentHUD();
	CurrentHUD->GetUIDuringTheGame()->SetNewTextToTextBlock(TextWhenDoorIsLocked);
}


