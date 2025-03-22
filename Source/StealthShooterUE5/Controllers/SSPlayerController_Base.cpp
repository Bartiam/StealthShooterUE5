// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController_Base.h"

//Include Inputs
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../Characters/SSCharacter_Base.h"

void ASSPlayerController_Base::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		SubSystem->AddMappingContext(MappingContext, 0);

	Character = Cast<ASSCharacter_Base>(GetCharacter());
}

void ASSPlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Locomotion Input
		EnhancedInputComponent->BindAction(LocomotionCharacterInput, ETriggerEvent::Triggered, this, &ASSPlayerController_Base::LocomotionCharacter);
		// Look Input
		EnhancedInputComponent->BindAction(LookCharacterInput, ETriggerEvent::Triggered, this, &ASSPlayerController_Base::LookCharacter);
	}
}

void ASSPlayerController_Base::LocomotionCharacter(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (IsValid(Character))
	{
		const FRotator RotationYaw = FRotator(0.f, GetControlRotation().Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::Y);

		Character->AddMovementInput(ForwardDirection, MoveVector.Y);
		Character->AddMovementInput(RightDirection, MoveVector.X);
	}
}

void ASSPlayerController_Base::LookCharacter(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}
