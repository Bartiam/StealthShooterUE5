// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSInteractableObject_Base.h"

#include "../SSData/SSTypes.h"

#include "SS_CardReader_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_CardReader_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()

public: // Functions
	
	ASS_CardReader_Base();

protected: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	ESSCardTypes NeededCard = ESSCardTypes::None_Card;

	// Materials for Door Light
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<UMaterial> OpenDoorMaterial;

protected: // Functions

	virtual void InteractableRelease_Implementation(const AActor* Interactor) override;

	virtual void BeginPlay() override;

private: // Variables

	TObjectPtr<class ASS_ImportantRoomsDoor_Base> CurrentDoor;
};
