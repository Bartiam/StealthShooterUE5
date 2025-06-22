// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_PickUpItem_Base.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"
#include "../Characters/SSPlayer_Base.h"
#include "../GAS/SS_AbilitySystemComponent.h"



ASS_PickUpItem_Base::ASS_PickUpItem_Base()
{
	// Enable physics
	ObjectCircled->SetSimulatePhysics(true);
}

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
	if (auto PlayerInventory = Cast<ASSPlayer_Base>(Interactor)->GetPlayerInventory())
	{
		// Trying add this item to the inventory
		if (PlayerInventory->TryAddItemToInventory(ItemObject))
			Destroy();
	}
}

void ASS_PickUpItem_Base::InteractableHeld_Implementation(AActor* Interactor)
{
	if (Interactor)
	{
		if (ItemObject->ItemInfo.GameplayEffect_Class)
		{
			ItemObject->ApplyGameplayEffectFromThisItem(Interactor);
			Destroy();
		}
	}
}

