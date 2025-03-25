// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController_Base.h"

#include "InputAction.h"
#include "InputMappingContext.h"

#include "../Input/SSEnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../GAS/SS_AbilitySystemComponent.h"
#include "../Input/SSInputConfig.h"

#include "../Characters/SSCharacter_Base.h"

void ASSPlayerController_Base::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(MappingContext, 0);
	}
}

void ASSPlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (USSEnhancedInputComponent* EnhancedInputComponent = Cast<USSEnhancedInputComponent>(InputComponent))
	{
		if (InputConfig)
		{
			
		}
	}
}
