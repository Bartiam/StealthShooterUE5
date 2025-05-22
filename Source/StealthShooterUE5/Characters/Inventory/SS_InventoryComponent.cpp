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

bool USS_InventoryComponent::TryAddItemToInventory(const FName ItemID)
{
	if (InventorySize <= InventorySlots.Num()) return false;

	if (CacheItemInfo.Find(ItemID))
	{
		InventorySlots.Add(CacheItemInfo[ItemID]);

		return true;
	}
	else
	{
		FString ContextAddInventory = FString();
		// Get item from data table
		if (FPickUpItemInfo* NewItem = DT_ItemInfo->FindRow<FPickUpItemInfo>(ItemID, ContextAddInventory))
		{
			// Add item to the inventory
			InventorySlots.Add(*NewItem);
			// Add item to the cache
			CacheItemInfo.Add(ItemID, *NewItem);

			return true;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT(""), *ContextAddInventory);
	}

	return false;
}

void USS_InventoryComponent::RemoveItemFromInventory(const int32 ItemIndex)
{
	
}

