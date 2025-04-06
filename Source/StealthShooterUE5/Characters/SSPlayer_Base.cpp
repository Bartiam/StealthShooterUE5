// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayer_Base.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

ASSPlayer_Base::ASSPlayer_Base()
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Create and base specifications for Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 150.f;
	SpringArmComponent->SocketOffset = FVector(0.f, 35.f, 70.f);

	// Create and base specifications for Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera Component"));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Player character movement base specifications
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void ASSPlayer_Base::BeginPlay()
{
	Super::BeginPlay();
}


