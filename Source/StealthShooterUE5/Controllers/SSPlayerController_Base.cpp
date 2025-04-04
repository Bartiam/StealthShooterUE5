// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController_Base.h"

#include "InputAction.h"
#include "InputMappingContext.h"

#include "../Input/SSInputConfig.h"
#include "../GAS/SS_AbilitySystemComponent.h"
#include "../Characters/SSPlayer_Base.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ASSPlayerController_Base::BeginPlay()
{
	Super::BeginPlay();

	CurrentCharacter = Cast<ASSPlayer_Base>(GetPawn());

	if (IsValid(CurrentCharacter))
		ASC = Cast<USS_AbilitySystemComponent>(CurrentCharacter->GetAbilitySystemComponent());

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(MappingContext, 0);
	}
}

void ASSPlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind character locomotion
		EnhancedInputComponent->BindAction(InputCharacterLocomotion, ETriggerEvent::Triggered, this, &ThisClass::LocomotionCharacter);
		// Bind character look
		EnhancedInputComponent->BindAction(InputCharacterLook, ETriggerEvent::Triggered, this, &ThisClass::LookCharacter);

		if (InputConfig)
		{
			// Bind Inputs from InputConfig
			for (const FSSInputActionBinds& ActionBind : InputConfig->InputActionBinds)
			{
				EnhancedInputComponent->BindAction(ActionBind.InputAction, ETriggerEvent::Triggered, this, &ThisClass::ActivateAbilityByInputIDHeld, ActionBind.ButtonInputID);
				EnhancedInputComponent->BindAction(ActionBind.InputAction, ETriggerEvent::Completed, this, &ThisClass::ActivateAbilityByInputIDReleased, ActionBind.ButtonInputID);
			}
		}
	}
}

void ASSPlayerController_Base::LocomotionCharacter(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (IsValid(CurrentCharacter))
	{
		// Find out which way is forward
		FRotator RotationYaw = FRotator(0.f, GetControlRotation().Yaw, 0.f);

		// Get forward vector
		FVector ForwardDirection = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::X);
		// Get right vector
		FVector RightDirection = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::Y);

		// Add movement
		CurrentCharacter->AddMovementInput(ForwardDirection, MoveVector.Y);
		CurrentCharacter->AddMovementInput(RightDirection, MoveVector.X);
	}
}

void ASSPlayerController_Base::LookCharacter(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void ASSPlayerController_Base::ActivateAbilityByInputIDHeld(const ESSInputID InputID)
{
	ASC->PressInputID(static_cast<int32>(InputID));
}

void ASSPlayerController_Base::ActivateAbilityByInputIDPressed(const ESSInputID InputID)
{
	
}

void ASSPlayerController_Base::ActivateAbilityByInputIDReleased(const ESSInputID InputID)
{
	ASC->ReleaseInputID(static_cast<int32>(InputID));
}


