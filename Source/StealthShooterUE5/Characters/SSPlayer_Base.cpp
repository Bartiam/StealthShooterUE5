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

	// Create and base specifications for Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera Component"));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Create and base specifications for Holster Component
	HolsterComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Holster"));
	HolsterComponent->SetupAttachment(GetMesh());
	HolsterComponent->SetLeaderPoseComponent(GetMesh(), true);

	// Create and base specifications for Jacket
	Jacket = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Jacket"));
	Jacket->SetupAttachment(GetMesh());
	Jacket->SetLeaderPoseComponent(GetMesh(), true);

	// Player character movement base specifications
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void ASSPlayer_Base::BeginPlay()
{
	Super::BeginPlay();

	CheckJacketOnTheCharacter();
}

void ASSPlayer_Base::CheckJacketOnTheCharacter()
{
	// If Jacket mesh is empty, destroy Jacket
	if (Jacket->MeshObject == nullptr)
	{
		Jacket->DestroyComponent();
	}
}
