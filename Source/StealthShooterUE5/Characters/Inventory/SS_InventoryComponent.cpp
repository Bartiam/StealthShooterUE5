// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_InventoryComponent.h"

#include "../../WorldObjects/SS_PickUpItem_Base.h"
#include "../SSPlayer_Base.h"
#include "Blueprint/UserWidget.h"



// Sets default values for this component's properties
USS_InventoryComponent::USS_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USS_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Inventory_Widget = CreateWidget<UUserWidget>(GetWorld(), Inventory_Class);

	InventoryItems.SetNum(GridSize.X * GridSize.Y);
}

UUserWidget* USS_InventoryComponent::GetInventoryWidget() const
{ return Inventory_Widget; }

bool USS_InventoryComponent::TryAddItemToInventory(USS_ItemObject* ItemObject)
{
	if (!ItemObject) return false;

	// Searching item info from DataTable
	for (int Index = 0; Index < InventoryItems.Num(); ++Index)
	{
		if (IsRoomAvailable(ItemObject, Index))
		{
			AddItemToInventory(ItemObject, Index);
			return true;
		}
	}

	for (int Index = 0; Index < InventoryItems.Num(); ++Index)
	{
		
	}

	return false;
}



void USS_InventoryComponent::AddItemToInventory(USS_ItemObject* ItemObject, const int& TopLeftIndex)
{
	TArray<FIntPoint> Tiles = ForEachIndex(ItemObject, TopLeftIndex);

	for (int i = 0; i < Tiles.Num(); ++i)
	{
		int CurrentIndex = TileToIndex(Tiles[i]);
		InventoryItems[CurrentIndex] = ItemObject;
	}
}



bool USS_InventoryComponent::IsRoomAvailable(const USS_ItemObject* ItemObject, const int& TopLeftIndex)
{
	TArray<FIntPoint> Tiles = ForEachIndex(ItemObject, TopLeftIndex);

	for (int i = 0; i < Tiles.Num(); ++i)
	{
		FIntPoint CurrentTile = Tiles[i];

		if (Tiles[i].X >= 0 && Tiles[i].Y >= 0 && Tiles[i].X < GridSize.X && Tiles[i].X < GridSize.Y)
		{
			int CurrentIndex = TileToIndex(CurrentTile);
			USS_ItemObject* CurrentItemInfo = nullptr;

			if (GetItemAtIndex(CurrentIndex, CurrentItemInfo))
			{
				if (CurrentItemInfo)
				{
					return false;
				}
			}
			else
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
	int FirstIndex_X = IndexToTile(TopLeftIndex).X;
	int FirstIndex_Y = IndexToTile(TopLeftIndex).Y;

	int LastIndex_X = FirstIndex_X + (ItemObject->ItemInfo.IconSize.X - 1);
	int LastIndex_Y = FirstIndex_Y + (ItemObject->ItemInfo.IconSize.Y - 1);

	TArray<FIntPoint> Tiles;

	for (int i = FirstIndex_X; i < LastIndex_X; ++i)
	{
		for (int j = FirstIndex_Y; j < LastIndex_Y; ++j)
		{
			Tiles.Add(FIntPoint(i, j));
		}
	}

	return Tiles;
}



FIntPoint USS_InventoryComponent::IndexToTile(const int& Index)
{
	return FIntPoint(Index % GridSize.X, Index / GridSize.X);
}

int USS_InventoryComponent::TileToIndex(const FIntPoint& Tile) const
{ return Tile.X + (Tile.Y * GridSize.X); }

bool USS_InventoryComponent::GetItemAtIndex(const int& Index, const USS_ItemObject* ItemObject)
{
	if (InventoryItems.IsValidIndex(Index))
	{
		ItemObject = InventoryItems[Index];
		return true;
	}

	return false;
}



void USS_InventoryComponent::RemoveItemFromInventory(const int32 ItemIndex)
{

}