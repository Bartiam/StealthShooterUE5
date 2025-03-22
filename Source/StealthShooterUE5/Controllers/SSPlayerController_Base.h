// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSPlayerController_Base.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class STEALTHSHOOTERUE5_API ASSPlayerController_Base : public APlayerController
{
	GENERATED_BODY()
	
protected: // Protected variables input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LocomotionCharacterInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookCharacterInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ReloadWeaponInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* CrouchCharacterInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* WalkCharacterInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractionCharacterInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ShootCharacterInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* AimCharacterInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* PauseMenuInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InventoryCharacterInput = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* MappingContext = nullptr;

private: // Private variables

	class ASSCharacter_Base* Character;

protected: // Protected functions

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private: // Private functions

	UFUNCTION()
	void LocomotionCharacter(const FInputActionValue& Value);

	UFUNCTION()
	void LookCharacter(const FInputActionValue& Value);
};
