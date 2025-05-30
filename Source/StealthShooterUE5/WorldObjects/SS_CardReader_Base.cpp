// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CardReader_Base.h"
#include "SS_ImportantRoomsDoor_Base.h"
#include "../Characters/SSCharacter_Base.h"
#include "../GAS/SS_AbilitySystemComponent.h"



ASS_CardReader_Base::ASS_CardReader_Base() 
{}

void ASS_CardReader_Base::OpenDoorWithCardreader(ESSCardTypes SelectedCard) const
{
	if (SelectedCard == CurrentDoor->GetNeededCard())
	{
		CurrentDoor->InteractableRelease_Implementation(nullptr);
	}
	else
	{

	}
}

void ASS_CardReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (CurrentDoor->GetIsDoorLock() && Interactor->Implements<UCharacterInterface>())
	{
		auto PlayerCharacter = ICharacterInterface::Execute_GetOwnerCharacter(Interactor);
		PlayerCharacter->GetAbilitySystemComponent()->PressInputID(static_cast<int32>(ESSInputID::Inventory_Input));
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

