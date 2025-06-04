// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Door_Base.h"

#include "../Core_C/SSHUD_Base.h"
#include "../Controllers/SSPlayerController_Base.h"
#include "../UserInterface/SS_DuringTheGame_Base.h"
#include "../Characters/SSCharacter_Base.h"
#include "../Characters/Inventory/SS_InventoryComponent.h"



ASS_Door_Base::ASS_Door_Base()
{
	// Create door frame and attach it to root component
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Frame"));
	DoorFrame->SetupAttachment(RootComponent);

	bIsCircledObject = false;
}



bool ASS_Door_Base::GetIsDoorLock() const
{ return bIsDoorLock; }



void ASS_Door_Base::SetIsDoorLock(const bool& NewValue)
{ 
	bIsDoorLock = NewValue;
	OnDoorStateChanged.Broadcast();
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



void ASS_Door_Base::OpenDoor(float Value) {}



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
		PlayerInventory->OnGetKeyFromInventory.AddDynamic(this, &ThisClass::BindOnGetKeyToOpenDoor);

		// Open player inventory
		auto PlayerASC = CurrentPlayer->GetAbilitySystemComponent();
		PlayerASC->PressInputID(static_cast<int32>(ESSInputID::Inventory_Input));
	}
}



void ASS_Door_Base::BindOnGetKeyToOpenDoor(FPickUpItemInfo ItemInfo, AActor* Interactor)
{
	auto CurrentPlayer = ICharacterInterface::Execute_GetOwnerCharacter(Interactor);
	CurrentPlayer->GetAbilitySystemComponent()->PressInputID(static_cast<int32>(ESSInputID::Inventory_Input));

	auto ReceivedItemAccessType = ItemInfo.KeyPepmission.ItemAccessType;
	auto ReceivedKeyPermission = ItemInfo.KeyPepmission;

	switch (ReceivedItemAccessType)
	{
	case ESSItemAccessType::None:
		SetTextInTheUIDuringTheGame(Interactor, TextWhenSelectedIncorrectKey);
		break;
	case ESSItemAccessType::Physical_Key:
		ReceivedKeyPermission.PhysKeyType == DoorKeyPermission.PhysKeyType ? SetIsDoorLock(false), InteractableRelease_Implementation(Interactor) :
			SetTextInTheUIDuringTheGame(Interactor, TextWhenSelectedIncorrectKey);
		break;
	case ESSItemAccessType::Card_Key:
		ReceivedKeyPermission.CardType == DoorKeyPermission.CardType ||
			(ReceivedKeyPermission.CardType == ESSCardType::Master_Card && DoorKeyPermission.CardType != ESSCardType::None) ?
			SetIsDoorLock(false), InteractableRelease_Implementation(Interactor) : SetTextInTheUIDuringTheGame(Interactor, TextWhenSelectedIncorrectKey);
		break;
	case ESSItemAccessType::Digital_Code:
		ReceivedKeyPermission.DigitalCode == DoorKeyPermission.DigitalCode ? SetIsDoorLock(false), InteractableRelease_Implementation(Interactor) :
			SetTextInTheUIDuringTheGame(Interactor, TextWhenSelectedIncorrectKey);
		break;
	}
}