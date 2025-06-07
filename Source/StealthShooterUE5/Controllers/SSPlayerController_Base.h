// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "../SSData/SSTypes.h"

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

	TObjectPtr<class ASSHUD_Base> CurrentHUD;

	TObjectPtr<class ASSPlayer_Base> CurrentCharacter;

	TObjectPtr<class USS_AbilitySystemComponent> ASC;

	FInputModeGameAndUI GameAndUIMode;

	FInputModeGameOnly GameOnlyMode;

private: // Functions

	UFUNCTION()
	void LocomotionCharacter(const FInputActionValue& Value);

	UFUNCTION()
	void LookCharacter(const FInputActionValue& Value);

	UFUNCTION()
	void ActivateAbilityByInputIDPressed(const ESSInputID InputID);

	UFUNCTION()
	void ActivateAbilityByInputIDReleased(const ESSInputID InputID);

	virtual void OnPossess(APawn* NewPawn) override;

public: // Functions

	ASSPlayerController_Base();

	UFUNCTION(BlueprintCallable)
	class ASSHUD_Base* GetCurrentHUD();

	void SetControllerCodeReaderMode(AActor* CameraTarget);

	void SetControllerBaseMode();
};
