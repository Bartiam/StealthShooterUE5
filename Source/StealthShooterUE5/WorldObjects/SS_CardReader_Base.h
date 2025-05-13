// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSInteractableObject_Base.h"
#include "SS_CardReader_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_CardReader_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()

public: // Functions

	ASS_CardReader_Base();

protected: // Functions

	virtual void InteractableRelease_Implementation(const AActor* Interactor) override;

	virtual void BeginPlay() override;
};
