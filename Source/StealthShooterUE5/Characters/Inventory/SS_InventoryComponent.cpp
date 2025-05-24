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

	InventoryItemsGrid.SetNum(Rows);
	for (int i = 0; i < InventoryItemsGrid.Num(); ++i)
		InventoryItemsGrid[i].SetNum(Columns);
}

UUserWidget* USS_InventoryComponent::GetInventoryWidget() const
{ return Inventory_Widget; }



bool USS_InventoryComponent::TryAddItemToInventory(USS_ItemObject* ItemObject)
{
	if (!ItemObject) return false;

	return false;
}

bool USS_InventoryComponent::isRoomAvailable()
{
	

	

	return true;
}