// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_PickUpItem_Base.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"



void ASS_PickUpItem_Base::BeginPlay()
{
	Super::BeginPlay();

	DT_ItemInfo = LoadObject<UDataTable>(this, TEXT("/Game/StealthShooter/Blueprints/InteractionObjects/DT_PickUpItems.DT_PickUpItems"));
	// Create item object
	ItemObject = NewObject<USS_ItemObject>(this);
	// Checking that the Data table found 
	if (auto ItemInfoFromDT = DT_ItemInfo->FindRow<FPickUpItemInfo>(Name_ID, FString("")))
		ItemObject->ItemInfo = *ItemInfoFromDT; // Assignment item info
}

void ASS_PickUpItem_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (Interactor->Implements<UCharacterInterface>())
	{
		auto PlayerInventory = ICharacterInterface::Execute_GetPlayerInventory(Interactor);

		if (PlayerInventory->TryAddItemToInventory(ItemObject))
			Destroy();
	}
}