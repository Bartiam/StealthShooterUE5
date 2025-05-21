// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSInteractableObject_Base.h"

#include "../Interfaces/CharacterInterface.h"

#include "SS_PickUpItem_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_PickUpItem_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Specifications")
	FName RowID = FName();

	UPROPERTY(BlueprintReadOnly, Category = "Item Specifications")
	TObjectPtr<UDataTable> DT_ItemID;

protected: // Functions

	virtual void BeginPlay() override;

	virtual void InteractableRelease_Implementation(AActor* Interactor) override;
};