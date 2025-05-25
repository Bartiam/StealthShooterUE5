// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../Interfaces/CharacterInterface.h"
#include "../../SSData/SSTypes.h"
#include "../../WorldObjects/SS_ItemObject.h"

#include "SS_InventoryComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHSHOOTERUE5_API USS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public: 

	USS_InventoryComponent();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	float TileSize = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UUserWidget> Inventory_Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Grid Size")
	int Rows = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Grid Size")
	int Columns = 0;

protected: // Functions

	virtual void BeginPlay() override;

private: // Variables

	TArray<TObjectPtr<USS_ItemObject>> InventoryItems;

	TObjectPtr<class UUserWidget> Inventory_Widget;

	bool bIsDirty = false;

private: // Functions

	bool isRoomAvailable(const USS_ItemObject* ItemObject, const int& TopLeftIndex);

	TArray<FIntPoint> ForEachIndex(const USS_ItemObject* ItemObject, const int& TopLeftIndex);

	FIntPoint IndexToTile(const int& Index) const;

	int TileToIndex(const FIntPoint& Tile) const;

	bool IsTileValid(const FIntPoint& Tile) const;

	USS_ItemObject* GetItemAtIndex(const int& Index);

	void AddItemAtInventory(USS_ItemObject* ItemObject, const int& Index);

public:	// Functions

	bool TryAddItemToInventory(USS_ItemObject* ItemObject);



	UFUNCTION(BlueprintCallable)
	class UUserWidget* GetInventoryWidget() const;
};
