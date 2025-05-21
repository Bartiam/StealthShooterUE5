// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_PickUpItem_Base.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"



void ASS_PickUpItem_Base::BeginPlay()
{
	Super::BeginPlay();
	
	DT_ItemID = LoadObject<UDataTable>(this, TEXT("/Game/StealthShooter/Blueprints/InteractionObjects/DT_PickUpItems.DT_PickUpItems"));
}

void ASS_PickUpItem_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	
}