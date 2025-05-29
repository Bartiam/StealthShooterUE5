// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSInteractableObject_Base.h"

#include "../Interfaces/CharacterInterface.h"
#include "SS_ItemObject.h"

#include "SS_PickUpItem_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_PickUpItem_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()

public: // Functions

	ASS_PickUpItem_Base();

protected: // Variables

	// Object name must be the same as the string name in data table
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item ID")
	FName Name_ID = FName();
	

private: // Variables

	TObjectPtr<USS_ItemObject> ItemObject;

	TObjectPtr<UDataTable> DT_ItemInfo;
	
protected: // Functions

	virtual void BeginPlay() override;

	virtual void InteractableRelease_Implementation(AActor* Interactor) override;

	virtual void InteractableHeld_Implementation(AActor* Interactor) override;
};