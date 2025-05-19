// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSInteractableObject_Base.h"

#include "../SSData/SSTypes.h"
#include "../Interfaces/CharacterInterface.h"

#include "SS_PickUpItem_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_PickUpItem_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()

public: // Functions

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FPickUpItemInfo GetItemInfo() const;

private: // Variables

	FPickUpItemInfo ItemInfo = FPickUpItemInfo();

protected: // Functions

	virtual void BeginPlay() override;

	virtual void InteractableRelease_Implementation(AActor* Interactor) override;
};