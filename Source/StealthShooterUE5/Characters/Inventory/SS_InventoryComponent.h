// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../SSPlayer_Base.h"

#include "SS_InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHSHOOTERUE5_API USS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private: // Variables

	TArray<FPickUpItemInfo> InventorySlots;

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 Capacity = 0;

public:	// Functions
	
	USS_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItemToInventory(class ASS_PickUpItem_Base* NewItem);

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromInventory(const int64 ItemID);



	
	

		
};
