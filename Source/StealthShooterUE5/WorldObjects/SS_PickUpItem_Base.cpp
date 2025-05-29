// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_PickUpItem_Base.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"
#include "../Characters/SSCharacter_Base.h"
#include "../GAS/SS_AbilitySystemComponent.h"



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
	// Verifying that the actor implements the interface
	if (Interactor->Implements<UCharacterInterface>())
	{
		// Get player inventory from ICharacterInterface
		auto PlayerInventory = ICharacterInterface::Execute_GetPlayerInventory(Interactor);
		// Trying add this item to the inventory
		if (PlayerInventory->TryAddItemToInventory(ItemObject))
			Destroy();
	}
}

void ASS_PickUpItem_Base::InteractableHeld_Implementation(AActor* Interactor)
{
	// Verifying that the actor implements the interface
	if (Interactor->Implements<UCharacterInterface>())
	{
		// Check ASC and Effect != nullptr
		if (auto CharacterASC = ICharacterInterface::Execute_GetOwnerCharacter(Interactor)->GetAbilitySystemComponent())
		{
			// Create effect context for gameplay effect 
			FGameplayEffectContextHandle EffectContext = CharacterASC->MakeEffectContext();
			// The source of the effect created
			EffectContext.AddSourceObject(this);
			// Create a specification for the effect
			FGameplayEffectSpecHandle SpecHandle = CharacterASC->MakeOutgoingSpec(ItemObject->ItemInfo.GameplayEffect_Class, 1.f, EffectContext);
			// Check valid
			if (SpecHandle.IsValid())
			{
				// Apply gameplay effect to character
				CharacterASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				Destroy();
			}
		}

	}

}
