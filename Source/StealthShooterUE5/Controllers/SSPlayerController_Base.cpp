// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerController_Base.h"

#include "InputAction.h"
#include "InputMappingContext.h"

#include "../Input/SSInputConfig.h"
#include "../GAS/SS_AbilitySystemComponent.h"
#include "../Characters/SSPlayer_Base.h"
#include "../Core_C/SSHUD_Base.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



void ASSPlayerController_Base::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentCharacter = Cast<ASSPlayer_Base>(GetPawn());

	if (IsValid(CurrentCharacter))
		ASC = Cast<USS_AbilitySystemComponent>(CurrentCharacter->GetAbilitySystemComponent());

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		SubSystem->AddMappingContext(MappingContext, 0);

	if (IsValid(GetHUD()))
		CurrentHUD = Cast<ASSHUD_Base>(GetHUD());

	SetControllerBaseMode();
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
				EnhancedInputComponent->BindAction(ActionBind.InputAction, ETriggerEvent::Started, this, &ThisClass::ActivateAbilityByInputIDPressed, ActionBind.ButtonInputID);
				EnhancedInputComponent->BindAction(ActionBind.InputAction, ETriggerEvent::Completed, this, &ThisClass::ActivateAbilityByInputIDReleased, ActionBind.ButtonInputID);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InputConfig is not set for %s!"), *GetName());
			return;
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



void ASSPlayerController_Base::ActivateAbilityByInputIDPressed(const ESSInputID InputID)
{
	if (ASC)
		ASC->PressInputID(static_cast<int32>(InputID));
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("NULL!!!!!"));
}

void ASSPlayerController_Base::ActivateAbilityByInputIDReleased(const ESSInputID InputID)
{ ASC->ReleaseInputID(static_cast<int32>(InputID)); }



void ASSPlayerController_Base::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	CurrentCharacter = Cast<ASSPlayer_Base>(NewPawn);

	if (IsValid(CurrentCharacter))
		ASC = Cast<USS_AbilitySystemComponent>(CurrentCharacter->GetAbilitySystemComponent());
}



ASSHUD_Base* ASSPlayerController_Base::GetCurrentHUD()
{ return CurrentHUD; }



void ASSPlayerController_Base::SetControllerCodeReaderMode(AActor* CameraTarget)
{
	SetViewTargetWithBlend(CameraTarget, 1.f);
	SetShowMouseCursor(true);
	SetInputMode(GameAndUIMode);
}



void ASSPlayerController_Base::SetControllerBaseMode()
{
	SetViewTargetWithBlend(GetPawn(), 1.f);
	SetShowMouseCursor(false);
	SetInputMode(GameOnlyMode);
}



ASSPlayerController_Base::ASSPlayerController_Base()
{
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}