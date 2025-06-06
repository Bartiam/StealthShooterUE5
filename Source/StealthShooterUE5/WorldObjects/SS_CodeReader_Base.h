// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SS_DisplayReader_Base.h"
#include "SS_CodeReader_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_CodeReader_Base : public ASS_DisplayReader_Base
{
	GENERATED_BODY()
	
public: // Functions

	ASS_CodeReader_Base();

protected: // Variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> CameraComponent;

	FInputModeGameAndUI GameAndUI;

protected: // Functions

	virtual void InteractableRelease_Implementation(AActor* Interactor) override;
};
