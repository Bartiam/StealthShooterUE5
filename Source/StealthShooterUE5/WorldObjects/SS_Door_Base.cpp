// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Door_Base.h"

#include "../Core_C/SSHUD_Base.h"
#include "../Controllers/SSPlayerController_Base.h"
#include "../UserInterface/SS_DuringTheGame_Base.h"
#include "../Characters/SSCharacter_Base.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"
#include "SS_DisplayReader_Base.h"



ASS_Door_Base::ASS_Door_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create door frame and attach it to root component
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Frame"));
	DoorFrame->SetupAttachment(RootComponent);

	SecondObjectCircled->SetupAttachment(DoorFrame);

	bIsCircledObject = false;
}



bool ASS_Door_Base::GetIsDoorLock() const
{ return bIsDoorLock; }



void ASS_Door_Base::SetIsDoorLock(const bool& NewValue)
{ 
	bIsDoorLock = NewValue;
	OnTryToOpenDoor.Broadcast();
}



void ASS_Door_Base::BeginPlay()
{
	Super::BeginPlay();

	BindCurveToTimeline(OpenDoorCurve, TimelineToOpenDoor);
}



void ASS_Door_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Promotes the timeline
	TimelineToOpenDoor.TickTimeline(DeltaTime);
}



void ASS_Door_Base::OpenDoor(float Value) 
{}



void ASS_Door_Base::BindCurveToTimeline(UCurveFloat* CurrentCurve, FTimeline& CurrentTimeline)
{
	// Checking that curve != nullptr
	if (CurrentCurve)
	{
		// Binds timeline to function
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ThisClass::OpenDoor);
		// Add curve to timeline
		CurrentTimeline.AddInterpFloat(CurrentCurve, TimelineProgress);
	}
}



void ASS_Door_Base::OpenAndBindToPlayerInventory(AActor* Interactor)
{
	if (Interactor && Interactor->Implements<UCharacterInterface>())
	{
		auto CurrentPlayer = ICharacterInterface::Execute_GetOwnerCharacter(Interactor);

		// Binds to inventory delegate
		auto PlayerInventory = ICharacterInterface::Execute_GetPlayerInventory(Interactor);
		PlayerInventory->OnGetKeyFromInventory.AddDynamic(this, &ThisClass::TryToOpenDoor);

		// Open player inventory
		auto PlayerASC = CurrentPlayer->GetAbilitySystemComponent();
		PlayerASC->PressInputID(static_cast<int32>(ESSInputID::Inventory_Input));
	}
}

void ASS_Door_Base::TryToOpenDoor(FPickUpItemInfo ItemInfo, AActor* Interactor)
{
	auto CurrentPlayer = ICharacterInterface::Execute_GetOwnerCharacter(Interactor);
	CurrentPlayer->GetAbilitySystemComponent()->PressInputID(static_cast<int32>(ESSInputID::Inventory_Input));
}



void ASS_Door_Base::GetReaderFromChildActors()
{
	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors);

	for (int i = 0; i < ChildActors.Num(); ++i)
	{
		if (ChildActors[i]->ActorHasTag(FName("Opposite Reader")))
			OppositeReader = Cast<ASS_DisplayReader_Base>(ChildActors[i]);
	}
}