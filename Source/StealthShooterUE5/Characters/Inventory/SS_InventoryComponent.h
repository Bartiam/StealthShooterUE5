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

protected: // Variables

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FPickUpItemInfo> InventorySlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 InventorySize = 0;

protected: // Functions

	virtual void BeginPlay() override;

public:	// Functions
	
	USS_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItemToInventory(const int32 ItemID);

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromInventory(const int32 ItemIndex);
		
};
