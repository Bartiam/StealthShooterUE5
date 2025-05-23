// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CardReader_Base.h"
#include "SS_ImportantRoomsDoor_Base.h"



ASS_CardReader_Base::ASS_CardReader_Base() 
{}

void ASS_CardReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (CurrentDoor->GetIsDoorLock())
	{
		CurrentDoor->SetIsDoorLock(false);
		CurrentDoor->SetMaterialToLightDoor(OpenDoorMaterial);
	}
	else
	{
		CurrentDoor->InteractableRelease_Implementation(Interactor);
	}
}

void ASS_CardReader_Base::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetParentActor()))
		CurrentDoor = Cast<ASS_ImportantRoomsDoor_Base>(GetParentActor());

	if (!CurrentDoor->GetIsDoorLock())
		CurrentDoor->SetMaterialToLightDoor(OpenDoorMaterial);
}

