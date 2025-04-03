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
	TObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputCharacterLocomotion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputCharacterLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class USSInputConfig> InputConfig;
	// -- Input Actions -- //

protected: // Functions

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private: // Variables

	UPROPERTY()
	TObjectPtr<class ASSPlayer_Base> CurrentCharacter;

private: // Functions

	UFUNCTION()
	void LocomotionCharacter(const FInputActionValue& Value);

	UFUNCTION()
	void LookCharacter(const FInputActionValue& Value);

	UFUNCTION()
	void ActivateAbilityByTagHold(const FGameplayTag InputTag);

	UFUNCTION()
	void ActivateAbilityByTagPressed(const FGameplayTag InputTag);

	UFUNCTION()
	void ActivateAbilityByTagReleased(const FGameplayTag InputTag);
};
