// Fill out your copyright notice in the Description page of Project Settings.


#include "SSInteractableObject_Base.h"

#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../UserInterface/SSInteractionWidget_Base.h"



// Sets default values
ASSInteractableObject_Base::ASSInteractableObject_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root Component"));
	SetRootComponent(DefaultRootComponent);

	// Create and set base specifications for MainMeshComponent
	ObjectCircled = CreateDefaultSubobject<UStaticMeshComponent>(FName("Circled Mesh"));
	ObjectCircled->SetupAttachment(RootComponent);
	ObjectCircled->ComponentTags.Add(FName("Circled"));
	ObjectCircled->SetRenderCustomDepth(false);

	// Create and set base specifications for InteractionWidget
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(FName("Interaction Widget"));
	InteractionWidget->SetupAttachment(ObjectCircled);
	InteractionWidget->SetCollisionProfileName(FName("NoCollision"));
	InteractionWidget->SetWidgetClass(InteractionWidget_Class);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetVisibility(false);
	
	// Get a link on widget class
	ConstructorHelpers::FClassFinder<USSInteractionWidget_Base> InteractionWidget_Finder
	(TEXT("/Game/StealthShooter/Blueprints/UserInterface/WBP_InteractObject.WBP_InteractObject_C"));
	// Set widget class
	InteractionWidget_Class = InteractionWidget_Finder.Class;
}

void ASSInteractableObject_Base::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidget_Poiner = CreateWidget<USSInteractionWidget_Base>(GetWorld(), InteractionWidget_Class);
	InteractionWidget->SetWidget(InteractionWidget_Poiner);
}

void ASSInteractableObject_Base::CanReceiveTrace_Implementation(bool bIsCanInteract)
{
	if (bIsCanInteract)
	{
		if (bIsCircledObject)
			ObjectCircled->SetRenderCustomDepth(true);

		InteractionWidget->SetVisibility(true);
		InteractionWidget_Poiner->PlayAnimation(InteractionWidget_Poiner->AppearMarkObject);
	}
	else
	{
		if (bIsCircledObject)
			ObjectCircled->SetRenderCustomDepth(false);

		InteractionWidget->SetVisibility(false);
		InteractionWidget_Poiner->ReverseAnimation(InteractionWidget_Poiner->AppearMarkObject);
	}
}