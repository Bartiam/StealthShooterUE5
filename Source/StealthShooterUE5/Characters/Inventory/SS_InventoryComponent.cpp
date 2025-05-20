// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_InventoryComponent.h"
#include "../../WorldObjects/SS_PickUpItem_Base.h"

// Sets default values for this component's properties
USS_InventoryComponent::USS_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USS_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool USS_InventoryComponent::AddItemToInventory(const int64 ItemID)
{
	if (Capacity > InventorySlots.Num())
	{
		
		return true;
	}

	return false;
}

void USS_InventoryComponent::RemoveItemFromInventory(const int8 ItemIndex)
{
	
}

