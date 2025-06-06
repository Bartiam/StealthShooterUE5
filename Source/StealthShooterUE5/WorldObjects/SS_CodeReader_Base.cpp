// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CodeReader_Base.h"
#include "SS_Door_Base.h"

#include "Camera/CameraComponent.h"

ASS_CodeReader_Base::ASS_CodeReader_Base()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);
}

void ASS_CodeReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (CurrentDoor->GetIsDoorLock())
	{

	}
	else
	{
		CurrentDoor->InteractableRelease_Implementation(Interactor);
	}
}