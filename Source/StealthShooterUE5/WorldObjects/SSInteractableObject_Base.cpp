// Fill out your copyright notice in the Description page of Project Settings.


#include "SSInteractableObject_Base.h"

#include "Components/WidgetComponent.h"



// Sets default values
ASSInteractableObject_Base::ASSInteractableObject_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create widget component
	PressWidget = CreateDefaultSubobject<UWidgetComponent>(FName("Interaction Widget"));
	PressWidget->SetupAttachment(RootComponent);

	// If not active, it goes into a dormant state.
	NetDormancy = DORM_DormantAll;
	// Set TPS for actor
	NetUpdateFrequency = 30.f;
	SetReplicates(true);
	bReplicates = true;
}

// Called when the game starts or when spawned
void ASSInteractableObject_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSInteractableObject_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

