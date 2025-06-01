// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CardReader_Base.h"
#include "SS_ImportantRoomsDoor_Base.h"
#include "../Characters/SSCharacter_Base.h"
#include "../GAS/SS_AbilitySystemComponent.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"



ASS_CardReader_Base::ASS_CardReader_Base() 
{}



void ASS_CardReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (CurrentDoor->GetIsDoorLock())
	{
		if (Interactor->Implements<UCharacterInterface>())
		{
			auto CurrentPlayer = ICharacterInterface::Execute_GetOwnerCharacter(Interactor);
			auto PlayerASC = CurrentPlayer->GetAbilitySystemComponent();
			PlayerASC->PressInputID(static_cast<int32>(ESSInputID::Inventory_Input));

			auto PlayerInventory = ICharacterInterface::Execute_GetPlayerInventory(Interactor);
			PlayerInventory->OnSearchItem.AddDynamic(this, &ThisClass::CheckItemObjectForOpenDoor);
		}
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



void ASS_CardReader_Base::CheckItemObjectForOpenDoor(FPickUpItemInfo ItemInfo, USS_InventoryComponent* PlayerInventory)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("WORKED!"));
	PlayerInventory->OnSearchItem.RemoveAll(this);


}

