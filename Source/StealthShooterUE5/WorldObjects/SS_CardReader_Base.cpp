// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CardReader_Base.h"
#include "SS_Door_Base.h"
#include "../Characters/SSCharacter_Base.h"
#include "../GAS/SS_AbilitySystemComponent.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"



ASS_CardReader_Base::ASS_CardReader_Base() 
{}



void ASS_CardReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (CurrentDoor->GetIsDoorLock())
	{
		CurrentDoor->OpenAndBindToPlayerInventory(Interactor);
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
		CurrentDoor = Cast<ASS_Door_Base>(GetParentActor());
}





