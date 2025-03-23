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

	
}

void ASSPlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ReloadWeaponInput, ETriggerEvent::Triggered, this, &ASSPlayerController_Base::ReloadWeaponCharacter);
	}
}

void ASSPlayerController_Base::ReloadWeaponCharacter(const FInputActionValue& Value)
{
	
}

