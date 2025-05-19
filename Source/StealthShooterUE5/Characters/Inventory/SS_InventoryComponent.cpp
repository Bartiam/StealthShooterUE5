// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_InventoryComponent.h"
#include "../../WorldObjects/SS_PickUpItem_Base.h"

// Sets default values for this component's properties
USS_InventoryComponent::USS_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InventorySlots.SetNum(Capacity);
}

bool USS_InventoryComponent::AddItemToInventory(ASS_PickUpItem_Base* NewItem)
{
	if (Capacity > InventorySlots.Num())
	{
		FPickUpItemInfo NewPickUpItemInfo;
		NewPickUpItemInfo = NewItem->GetItemInfo();
		

		return true;
	}
	return false;
}

void USS_InventoryComponent::RemoveItemFromInventory(const int64 ItemID)
{
}

