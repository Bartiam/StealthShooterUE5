// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSPlayerController_Base.generated.h"

class UInputAction;


UCLASS()
class STEALTHSHOOTERUE5_API ASSPlayerController_Base : public APlayerController
{
	GENERATED_BODY()

protected: // Variables

	// -- Input Actions -- //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LocomotionCharacterInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookCharacterInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> MappingContext;

	// -- Input Actions -- //

protected: // Functions

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
};
