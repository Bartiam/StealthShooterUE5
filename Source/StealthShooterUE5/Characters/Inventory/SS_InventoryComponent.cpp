// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_InventoryComponent.h"

#include "../../WorldObjects/SS_PickUpItem_Base.h"
#include "../SSPlayer_Base.h"
#include "../../Controllers/SSPlayerController_Base.h"
#include "../../Core_C/SSHUD_Base.h"
#include "../../UserInterface/SS_DuringTheGame_Base.h"



// Sets default values for this component's properties
USS_InventoryComponent::USS_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void USS_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set size for inventory
	InventoryItems.SetNum(Rows * Columns);
}



bool USS_InventoryComponent::TryAddItemToInventory(USS_ItemObject* ItemObject)
{
	// return, if the object equals nullptr
	if (!ItemObject) return false;

	for (int Index = 0; Index < InventoryItems.Num(); ++Index)
	{
		if (isRoomAvailable(ItemObject, Index))
		{
			// if the room is available add item to inventory
			AddItemAtInventory(ItemObject, Index);
			return true;
		}
	}

	if (ItemObject->ItemInfo.ItemIcon_Rotated)
	{
		ItemObject->RotateImage();

		for (int Index = 0; Index < InventoryItems.Num(); ++Index)
		{
			if (isRoomAvailable(ItemObject, Index))
			{
				// if the room is available add rotated item to inventory
				AddItemAtInventory(ItemObject, Index);
				return true;
			}
		}
	}

	if (auto InventoryOwner = Cast<ASSCharacter_Base>(GetOwner()))
	{
		auto CurrentHUD = InventoryOwner->GetOwnerPlayerController()->GetCurrentHUD();
		CurrentHUD->GetUIDuringTheGame()->SetNewTextToTextBlock(TextWhenInventoryNoRoom);
	}

	return false;
}



TMap<USS_ItemObject*, FIntPoint> USS_InventoryComponent::GetAllInventoryItems()
{
	TMap<USS_ItemObject*, FIntPoint> AllInventoryItems;

	for (int Index = 0; Index < InventoryItems.Num(); ++Index)
	{
		TObjectPtr<USS_ItemObject> CurrentItem = InventoryItems[Index];

		if (CurrentItem)
		{
			if (!AllInventoryItems.Find(CurrentItem))
			{
				AllInventoryItems.Add(CurrentItem, IndexToTile(Index));
			}
		}
	}

	return AllInventoryItems;
}



void USS_InventoryComponent::RemoveItemFromInventory(USS_ItemObject* ItemObject)
{
	if (ItemObject)
	{
		for (int i = 0; i < InventoryItems.Num(); ++i)
		{
			if (InventoryItems[i] == ItemObject)
			{
				InventoryItems[i] = nullptr;
			}
		}

		OnInventoryChanged.Broadcast();
	}
}

void USS_InventoryComponent::CallOnGetKeyFromInventory(const FPickUpItemInfo& ItemInfo, AActor* Interactor)
{
	OnGetKeyFromInventory.Broadcast(ItemInfo, Interactor);
}



bool USS_InventoryComponent::isRoomAvailable(const USS_ItemObject* ItemObject, const int& TopLeftIndex)
{
	// Get tiles for adding object to inventory
	TArray<FIntPoint> Tiles = ForEachIndex(ItemObject, TopLeftIndex);

	for (int Index = 0; Index < Tiles.Num(); ++Index)
	{
		if (IsTileValid(Tiles[Index]))
		{
			// Get current index from current tile
			int CurrentIndex = TileToIndex(Tiles[Index]);
			// Get object from inventory by CurrentIndex
			USS_ItemObject* CurrentItemObject = GetItemAtIndex(CurrentIndex);
			// Checking that object != nullptr
			if (CurrentItemObject)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}



TArray<FIntPoint> USS_InventoryComponent::ForEachIndex(const USS_ItemObject* ItemObject, const int& TopLeftIndex)
{
	TArray<FIntPoint> Tiles;
	// Get a tile from the received index
	FIntPoint CurrentTile = IndexToTile(TopLeftIndex);
	// Get the latest indexes for object in the inventory
	int LastIndex_X = CurrentTile.X + (ItemObject->ItemInfo.IconSize.X - 1);
	int LastIndex_Y = CurrentTile.Y + (ItemObject->ItemInfo.IconSize.Y - 1);

	for (int i = CurrentTile.X; i <= LastIndex_X; ++i)
	{
		for (int j = CurrentTile.Y; j <= LastIndex_Y; ++j)
		{
			// Add tiles for adding object to the inventory
			Tiles.Add(FIntPoint(i, j));
		}
	}

	return Tiles;
}



FIntPoint USS_InventoryComponent::IndexToTile(const int& Index) const
{ 
	return FIntPoint(Index % Columns, Index / Columns); // Transformation index to tile
}



int USS_InventoryComponent::TileToIndex(const FIntPoint& Tile) const
{
	return Tile.X + (Tile.Y * Columns); // Transformation tile to index
}



bool USS_InventoryComponent::IsTileValid(const FIntPoint& Tile) const
{ 
	return Tile.X >= 0 && Tile.Y >= 0 && Tile.X < Columns && Tile.Y < Rows;
}



USS_ItemObject* USS_InventoryComponent::GetItemAtIndex(const int& Index)
{
	if (InventoryItems.IsValidIndex(Index))
	{
		return InventoryItems[Index];
	}

	return nullptr;
}



void USS_InventoryComponent::AddItemAtInventory(USS_ItemObject* ItemObject, const int& Index)
{
	// Get tiles for adding object to inventory
	TArray<FIntPoint> Tiles = ForEachIndex(ItemObject, Index);

	for (int i = 0; i < Tiles.Num(); ++i)
	{
		// Adding object in the inventory
		int ObjectIndex = TileToIndex(Tiles[i]);
		InventoryItems[ObjectIndex] = ItemObject;
	}

	OnInventoryChanged.Broadcast();
}
