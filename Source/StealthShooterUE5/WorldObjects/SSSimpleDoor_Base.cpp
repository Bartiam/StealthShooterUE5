// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSimpleDoor_Base.h"

#include "Net/UnrealNetwork.h"
#include "Components/BoxComponent.h"

// Sets default values
ASSSimpleDoor_Base::ASSSimpleDoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Setup base specifications of Platband
	Platband = CreateDefaultSubobject<UStaticMeshComponent>(FName("Platband"));
	SetRootComponent(Platband);

	// Setup base specifications of door
	Door = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door"));
	Door->SetupAttachment(Platband);

	// Setup base specifications of overlap box collision
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(FName("Overlap Box"));
	OverlapBox->SetupAttachment(Platband);

	NetDormancy = DORM_DormantAll;
	NetUpdateFrequency = 30.f;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASSSimpleDoor_Base::BeginPlay()
{
	Super::BeginPlay();
}

void ASSSimpleDoor_Base::Interactable_Implementation()
{
	Server_OpenDoor();
	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("ITS WORKED!!!"));
}

void ASSSimpleDoor_Base::Server_OpenDoor_Implementation()
{
	if (GetLocalRole() != ROLE_Authority) return;

	GetWorldTimerManager().SetTimer(TimerToOpenDoor, this, &ThisClass::ChangeRotationDoor, 0.01, true);
}

void ASSSimpleDoor_Base::ChangeRotationDoor_Implementation()
{
	FRotator NewRotation = Door->GetComponentRotation();
	NewRotation = FRotator(NewRotation.Pitch, NewRotation.Yaw + 0.6f, NewRotation.Roll);
	Door->SetRelativeRotation(NewRotation, true);
}