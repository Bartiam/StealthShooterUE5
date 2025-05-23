// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../Interfaces/CharacterInterface.h"
#include "../../SSData/SSTypes.h"

#include "SS_InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHSHOOTERUE5_API USS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	float TileSize = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UUserWidget> Inventory_Class;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FPickUpItemInfo> InventoryItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	FIntPoint GridSize = FIntPoint();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UDataTable> DT_ItemInfo;

	TMap<FName, FPickUpItemInfo> Cache_ItemInfo;

protected: // Functions

	virtual void BeginPlay() override;

private: // Variables

	TObjectPtr<class UUserWidget> Inventory_Widget;
		

public:	// Functions

	USS_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	class UUserWidget* GetInventoryWidget() const;

	UFUNCTION(BlueprintCallable)
	bool TryAddItemToInventory(const FName ItemID);

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromInventory(const int32 ItemIndex);
};
