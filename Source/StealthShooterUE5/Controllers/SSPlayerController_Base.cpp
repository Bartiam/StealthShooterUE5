// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController_Base.h"

//Include Inputs
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../GAS/SS_AbilitySystemComponent.h"

#include "../Characters/SSCharacter_Base.h"

void ASSPlayerController_Base::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(MappingContext, 0);
	}

	CurrentCharacter = Cast<ASSCharacter_Base>(GetPawn());
}

void ASSPlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LocomotionCharacterInput, ETriggerEvent::Triggered, this, &ASSPlayerController_Base::LocomotionCharacter);
	}
}

void ASSPlayerController_Base::LocomotionCharacter(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (IsValid(CurrentCharacter))
	{
		const FRotator RotationYaw = FRotator(0.f, GetControlRotation().Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::Y);

		CurrentCharacter->AddMovementInput(ForwardDirection, MoveVector.Y);
		CurrentCharacter->AddMovementInput(RightDirection, MoveVector.X);
	}
}