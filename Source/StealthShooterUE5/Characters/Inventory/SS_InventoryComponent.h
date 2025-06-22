// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../SSData/SSTypes.h"
#include "../../WorldObjects/SS_ItemObject.h"

#include "SS_InventoryComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGetKeyFromInventory, FPickUpItemInfo, ItemInfo, AActor*, Interactor);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class STEALTHSHOOTERUE5_API USS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public: 

	USS_InventoryComponent();

	UPROPERTY(BlueprintAssignable)
	FOnGetKeyFromInventory OnGetKeyFromInventory;

protected: // Variables

	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	float TileSize = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	FText TextWhenInventoryNoRoom = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Grid Size")
	int Rows = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Grid Size")
	int Columns = 0;

protected: // Functions

	virtual void BeginPlay() override;

private: // Variables

	TArray<TObjectPtr<USS_ItemObject>> InventoryItems;

private: // Functions

	TArray<FIntPoint> ForEachIndex(const USS_ItemObject* ItemObject, const int& TopLeftIndex);

	FIntPoint IndexToTile(const int& Index) const;

	bool IsTileValid(const FIntPoint& Tile) const;

	USS_ItemObject* GetItemAtIndex(const int& Index);

public: // Variables

	UPROPERTY(BlueprintReadWrite)
	bool bIsItemWasSpawnedFromInventory = false;

public:	// Functions

	UFUNCTION(BlueprintCallable)
	bool TryAddItemToInventory(USS_ItemObject* ItemObject);

	UFUNCTION(BlueprintCallable)
	void AddItemAtInventory(USS_ItemObject* ItemObject, const int& Index);

	UFUNCTION(BlueprintCallable)
	int TileToIndex(const FIntPoint& Tile) const;

	UFUNCTION(BlueprintCallable)
	bool isRoomAvailable(const USS_ItemObject* ItemObject, const int& TopLeftIndex);

	UFUNCTION(BlueprintCallable)
	TMap<USS_ItemObject*, FIntPoint> GetAllInventoryItems();

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromInventory(USS_ItemObject* ItemObject);

	UFUNCTION(BlueprintCallable)
	void CallOnGetKeyFromInventory(const FPickUpItemInfo& ItemInfo, AActor* Interactor);
};
