// Fill out your copyright notice in the Description page of Project Settings.


#include "SSInteractableObject_Base.h"

#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../UserInterface/SSInteractionWidget_Base.h"



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
	InteractionWidget->SetupAttachment(ObjectCircled);
	InteractionWidget->SetCollisionProfileName(FName("NoCollision"));
	InteractionWidget->SetWidgetClass(InteractionWidget_Class);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
	// Get a link on widget class
	ConstructorHelpers::FClassFinder<USSInteractionWidget_Base> InteractionWidget_Finder
	(TEXT("/Game/StealthShooter/Blueprints/UserInterface/WBP_InteractObject.WBP_InteractObject_C"));
	// Set widget class
	InteractionWidget_Class = InteractionWidget_Finder.Class;


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

void ASSInteractableObject_Base::CanReceiveTrace_Implementation(bool bIsCanInteract)
{
	auto NewWidget = CreateWidget<USSInteractionWidget_Base>(GetWorld(), InteractionWidget_Class);

	if (bIsCanInteract)
	{
		InteractionWidget->SetWidget(NewWidget);
		InteractionWidget->SetVisibility(true);
		NewWidget->PlayAnimation(NewWidget->AppearMarkObject);
	}
	else
	{
		InteractionWidget->SetVisibility(false);
	}
		
}