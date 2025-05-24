// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Interfaces/CharacterInterface.h"
#include "../../SSData/SSTypes.h"
#include "Containers/Map.h"
#include "../../WorldObjects/SS_ItemObject.h"

#include "SS_InventoryComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHSHOOTERUE5_API USS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TArray<TObjectPtr<USS_ItemObject>> InventoryItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	float TileSize = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UUserWidget> Inventory_Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	FIntPoint GridSize = FIntPoint();

protected: // Functions

	virtual void BeginPlay() override;

private: // Variables

	

	TObjectPtr<class UUserWidget> Inventory_Widget;

	bool bIsDirty = false;
	
private: // Functions

	bool IsRoomAvailable(const USS_ItemObject* ItemObject, const int& TopLeftIndex);

	TArray<FIntPoint> ForEachIndex(const USS_ItemObject* ItemObject, const int& TopLeftIndex);

	FIntPoint IndexToTile(const int& Index);

	int TileToIndex(const FIntPoint& Tile) const;

	bool GetItemAtIndex(const int& CurrentIndex, const USS_ItemObject* ItemObject);

	void AddItemToInventory(USS_ItemObject* ItemObject, const int& TopLeftIndex);

public:	// Functions

	USS_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	class UUserWidget* GetInventoryWidget() const;

	UFUNCTION(BlueprintCallable)
	bool TryAddItemToInventory(USS_ItemObject* ItemObject);

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromInventory(const int32 ItemIndex);
};
