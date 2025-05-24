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

	// Set rows for inventory
	InventoryItems.SetNum(Rows);
	// Set columns for inventory
	for (int i = 0; i < InventoryItems.Num(); ++i)
		InventoryItems[i].SetNum(Columns);
}

UUserWidget* USS_InventoryComponent::GetInventoryWidget() const
{ return Inventory_Widget; }



bool USS_InventoryComponent::TryAddItemToInventory(USS_ItemObject* ItemObject)
{
	// return, if the object equals nullptr
	if (!ItemObject) return false;

	FIntPoint IconSize = ItemObject->ItemInfo.IconSize;

	// Tiles for new object
	TArray<FIntPoint> TilesToPost;
	// Checking that there is a place in the inventory 
	if (isRoomAvailable(IconSize, TilesToPost))
	{
		for (int i = 0; i < TilesToPost.Num(); ++i)
		{
			InventoryItems[TilesToPost[i].X][TilesToPost[i].Y] = ItemObject;
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::FromInt(TilesToPost[i].X) + ", " + FString::FromInt(TilesToPost[i].Y));
		}
		return true;
	}

	return false;
}

bool USS_InventoryComponent::isRoomAvailable(const FIntPoint IconSize, TArray<FIntPoint>& OutTilesToPost)
{
	for (int i = 0; i < InventoryItems.Num(); ++i)
	{
		for (int j = 0; j < InventoryItems[i].Num(); ++j)
		{
			if (InventoryItems[i][j])
			{
				OutTilesToPost.Empty();
			}
			else
			{
				OutTilesToPost.Add(FIntPoint(i, j));
			}

			
		}
	}

	

	return false;
}