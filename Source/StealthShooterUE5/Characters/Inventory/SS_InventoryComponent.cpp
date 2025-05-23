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
}

UUserWidget* USS_InventoryComponent::GetInventoryWidget() const
{ return Inventory_Widget; }

bool USS_InventoryComponent::TryAddItemToInventory(const FName ItemID)
{
	// Searching item info from TMap Cache
	if (auto NewItemInfo = Cache_ItemInfo.Find(ItemID))
	{
		for (int i = 0; i < InventoryItems.Num(); ++i)
		{

		}

		return true;
	}


	// Searching item info from DataTable
	if (auto NewItemInfo = DT_ItemInfo->FindRow<FPickUpItemInfo>(ItemID, FString("")))
	{
		for (int i = 0; i < InventoryItems.Num(); ++i)
		{

		}

		return true;
	}

	return false;
}


bool USS_InventoryComponent::IsRoomAvailable(const FPickUpItemInfo& ItemInfo, const int& TopLeftIndex)
{
	return true;
}




void USS_InventoryComponent::RemoveItemFromInventory(const int32 ItemIndex)
{
	
}

