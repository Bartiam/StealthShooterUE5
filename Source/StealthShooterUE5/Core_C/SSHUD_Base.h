// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SSHUD_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASSHUD_Base : public AHUD
{
	GENERATED_BODY()
	
private: // Variables

	TObjectPtr<class UUserWidget> InventoryWidget;

	TObjectPtr<class USS_UIDuringTheGame_Base> UI_DuringTheGameWidget;

public: // Functions

	UFUNCTION()
	USS_UIDuringTheGame_Base* GetUIDuringTheGame();

	UFUNCTION()
	UUserWidget* GetInventoryWidget();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UUserWidget> Inventory_Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UUserWidget> UI_DuringTheGame_Class;

protected: // Functions

	virtual void BeginPlay() override;
};
