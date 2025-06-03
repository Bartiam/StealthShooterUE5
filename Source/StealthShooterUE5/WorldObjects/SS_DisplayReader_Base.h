// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSInteractableObject_Base.h"

#include "SS_DisplayReader_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_DisplayReader_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()
	
public: // Functions

	ASS_DisplayReader_Base();

protected: // Variables

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> DisplayWidget_Component;

protected: // Functions

	virtual void BeginPlay() override;

private: // Variables

	TObjectPtr<class UUserWidget> DisplayWidget_Pointer;
};
