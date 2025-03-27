// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController_Base.h"

#include "InputAction.h"
#include "InputMappingContext.h"

#include "../Input/SSInputConfig.h"
#include "../GAS/SS_AbilitySystemComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../Characters/SSCharacter_Base.h"

void ASSPlayerController_Base::BeginPlay()
{
	Super::BeginPlay();

	CurrentCharacter = Cast<ASSCharacter_Base>(GetPawn());

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
		if (InputConfig)
		{
			for (const FSSInputActionBinds& ActionBind : InputConfig->InputActionBinds)
			{
				EnhancedInputComponent->BindAction(ActionBind.InputAction, ETriggerEvent::Triggered, this, &ThisClass::LocomotionCharacter, ActionBind.InputTag);
			}
		}
	}
}

void ASSPlayerController_Base::LocomotionCharacter(const FGameplayTag InputTag)
{
	bool test = CurrentCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(InputTag.GetSingleTagContainer());

	if (!test)
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, FString("FDSFsedf"));
}
