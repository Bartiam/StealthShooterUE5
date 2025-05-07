// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayer_Base.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Controllers/SSPlayerController_Base.h"

#include "../GAS/SS_AbilitySystemComponent.h"

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
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 14.f;

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

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ASSPlayer_Base::BeginPlay()
{
	Super::BeginPlay();

	CheckJacketOnTheCharacter();

	// Activate line trace ability
	GetWorldTimerManager().SetTimer(TimerToSearching, this, &ThisClass::SearchingObjectsLinetrace, 0.1f, true);
}

void ASSPlayer_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(NewController))
		CurrentPlayerController = Cast<ASSPlayerController_Base>(NewController);
}

void ASSPlayer_Base::CheckJacketOnTheCharacter()
{
	// If Jacket mesh is empty, destroy Jacket
	if (Jacket->MeshObject == nullptr)
	{
		Jacket->DestroyComponent();
	}
}

void ASSPlayer_Base::SearchingObjectsLinetrace()
{
	FHitResult HitResult;

	FVector CameraLocation = CameraComponent->GetComponentLocation();
	// The distance at which the beam hits
	FVector EndSphereTrace = CameraLocation + (CameraComponent->GetForwardVector() * SphereTraceLength);

	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), CameraLocation, EndSphereTrace, SphereTraceRadius,
		ETraceTypeQuery::TraceTypeQuery1, true, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true);

	// Checking that the actor has an interface
	if (HitResult.GetActor() && HitResult.GetActor()->Implements<UInteractable>())
	{
		// Saving the link to the actor 
		HitActorTrace = HitResult.GetActor();
		// Call funtion from interface with true
		IInteractable::Execute_CanReceiveTrace(HitActorTrace, true);
	}
	else
	{
		// Verifying that the actor is valid
		if (HitActorTrace != nullptr)
		{
			// Call funtion from interface with false
			IInteractable::Execute_CanReceiveTrace(HitActorTrace, false);
			// Set the actor is nullptr
			HitActorTrace = nullptr;
		}
	}
}

ASSPlayer_Base* ASSPlayer_Base::GetOwnerPlayer_Implementation()
{ return this; }

ASSPlayerController_Base* ASSPlayer_Base::GetOwnerPlayerController_Implementation()
{ return CurrentPlayerController; }