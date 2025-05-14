// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Door_Base.h"

ASS_Door_Base::ASS_Door_Base()
{
	// Create door frame and attach it to root component
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Frame"));
	DoorFrame->SetupAttachment(RootComponent);
}

void ASS_Door_Base::OpenDoor(float Value) {};