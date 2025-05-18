// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSInteractableObject_Base.h"
#include "SS_SmallPhysObject_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_SmallPhysObject_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()
	
public: // functions

	ASS_SmallPhysObject_Base();

protected: // functions 

	virtual void InteractableRelease_Implementation(const AActor* Interactor) override;

	virtual void InteractableHeld_Implementation(const AActor* Interactor) override;
};
