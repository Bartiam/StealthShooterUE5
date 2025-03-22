// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacter_Base.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASSCharacter_Base::ASSCharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Create spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("Spring Arm")));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = true;
	SpringArm->bUsePawnControlRotation = true;

	SpringArm->TargetArmLength = 300.f;
	SpringArm->SocketOffset.Z = 100.f;

	// Create camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera Component")));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->bUsePawnControlRotation = true;

	// Configure character movement
}

// Called when the game starts or when spawned
void ASSCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASSCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

