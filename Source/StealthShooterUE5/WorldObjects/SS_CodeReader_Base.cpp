// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CodeReader_Base.h"
#include "SS_Door_Base.h"
#include "../Controllers/SSPlayerController_Base.h"
#include "../Core_C/SSHUD_Base.h"
#include "../UserInterface/SS_DuringTheGame_Base.h"

#include "Camera/CameraComponent.h"

ASS_CodeReader_Base::ASS_CodeReader_Base()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera Component"));
	CameraComponent->SetupAttachment(RootComponent);
}

void ASS_CodeReader_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (CurrentDoor->GetIsDoorLock())
	{
		auto CurrentPlayerController = ICharacterInterface::Execute_GetOwnerCharacterController(Interactor);
		CurrentPlayerController->SetViewTargetWithBlend(this, 1.f);
		CurrentPlayerController->SetShowMouseCursor(true);
		CurrentPlayerController->SetInputMode(GameAndUI);

		if (auto CurrentHUD = Cast<ASSHUD_Base>(CurrentPlayerController->GetHUD()))
			CurrentHUD->GetUIDuringTheGame()->RemoveFromParent();
	}
	else
	{
		CurrentDoor->InteractableRelease_Implementation(Interactor);
	}
}