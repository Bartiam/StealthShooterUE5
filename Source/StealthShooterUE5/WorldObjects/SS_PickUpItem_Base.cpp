// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_PickUpItem_Base.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"



FPickUpItemInfo ASS_PickUpItem_Base::GetItemInfo() const
{ return ItemInfo; }

void ASS_PickUpItem_Base::BeginPlay()
{
	Super::BeginPlay();
	

}

void ASS_PickUpItem_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (Interactor->Implements<UCharacterInterface>())
	{
		auto PlayerInventory = ICharacterInterface::Execute_GetPlayerInventory(Interactor);

		if (PlayerInventory->AddItemToInventory(this))
			Destroy();
	}
}