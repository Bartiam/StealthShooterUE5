// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayer_Base.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Inventory/SS_InventoryComponent.h"
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
	SpringArmComponent->TargetArmLength = 130.f;
	SpringArmComponent->SocketOffset = FVector(0.f, 40.f, 55.f);

	// Create and base specifications for Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera Component"));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Create and base specifications for Holster Component
	HolsterComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Holster"));
	HolsterComponent->SetupAttachment(GetMesh());

	// Create and base specifications for Jacket
	Jacket = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Jacket"));
	Jacket->SetupAttachment(GetMesh());

	// Player character movement base specifications
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	// Create inventory component
	InventoryComponent = CreateDefaultSubobject<USS_InventoryComponent>(FName("Inventory Component"));

}

void ASSPlayer_Base::BeginPlay()
{
	Super::BeginPlay();

	CheckJacketOnTheCharacter();

	// Activate Sphere Trace
	GetWorldTimerManager().SetTimer(TimerToSearching, this, &ThisClass::SearchingObjectsLinetrace, 0.1f, true);
}

void ASSPlayer_Base::CheckJacketOnTheCharacter()
{
	// If Jacket mesh is empty, destroy Jacket
	if (Jacket->MeshObject == nullptr)
	{
		Jacket->DestroyComponent();
		return;
	}
}

void ASSPlayer_Base::SearchingObjectsLinetrace()
{
	FHitResult HitResult;

	FVector CameraLocation = CameraComponent->GetComponentLocation();
	// The distance at which the beam hits
	FVector EndSphereTrace = CameraLocation + (CameraComponent->GetForwardVector() * SphereTraceLength);
	// Activate sphere trace
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), CameraLocation, EndSphereTrace, SphereTraceRadius,
		ETraceTypeQuery::TraceTypeQuery1, true, IgnoreActors, EDrawDebugTrace::None, HitResult, true);

	// Checking that the actor and HitActorTrace != nullptr. The actor has an interface UInteractable.
	// Checking that the actor's component has tag "Main Object".
	if (HitResult.GetActor() && HitResult.GetActor()->Implements<UInteractable>()
		&& !HitActorTrace && HitResult.GetComponent()->ComponentHasTag(FName("Circled")))
	{
		// Saving the link to the actor
		HitActorTrace = HitResult.GetActor();
		// Call funñtion from interface with true
		IInteractable::Execute_CanReceiveTrace(HitActorTrace, true);
	}
	else if (HitResult.GetActor() != HitActorTrace || 
		(HitResult.GetActor() != nullptr && !HitResult.GetComponent()->ComponentHasTag(FName("Circled"))))
	{
		// Verifying that the actor is valid
		if (HitActorTrace != nullptr)
		{
			// Call function from interface with false
			IInteractable::Execute_CanReceiveTrace(HitActorTrace, false);
			// Set the actor is nullptr
			HitActorTrace = nullptr;
		}
	}
}