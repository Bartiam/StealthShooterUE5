// Fill out your copyright notice in the Description page of Project Settings.


#include "SSInteractableObject_Base.h"

#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ASSInteractableObject_Base::ASSInteractableObject_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and set base specifications for OverlapBox
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(FName("Overlap Box"));
	SetRootComponent(OverlapBox);

	// Create and set base specifications for MainMeshComponent
	ObjectCircled = CreateDefaultSubobject<UStaticMeshComponent>(FName("Main Mesh Component"));
	ObjectCircled->SetupAttachment(RootComponent);

	// Create and set base specifications for InteractionWidget
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(FName("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetCollisionProfileName(FName("NoCollision"));

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
	
	if (OverlapBox)
	{
		OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxCollisionBeginOverlap);
		OverlapBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnBoxCollisionEndOverlap);
	}
}

// Called every frame
void ASSInteractableObject_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASSInteractableObject_Base::CanReceiveTrace_Implementation(bool bIsCanInteract)
{

}

void ASSInteractableObject_Base::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ASSInteractableObject_Base::OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}