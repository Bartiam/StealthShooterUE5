// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SS_DisplayReader_Base.h"
#include "SS_CardReader_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_CardReader_Base : public ASS_DisplayReader_Base
{
	GENERATED_BODY()

public: // Functions
	
	ASS_CardReader_Base();

public: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<class ASS_Door_Base> CurrentDoor;

protected: // Functions

	virtual void InteractableRelease_Implementation(AActor* Interactor) override;

	virtual void BeginPlay() override;


};
