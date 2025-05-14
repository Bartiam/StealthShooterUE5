// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ImportantRoomsDoor_Base.h"



// Sets default values
ASS_ImportantRoomsDoor_Base::ASS_ImportantRoomsDoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create piston and attch it to door frame
	Piston = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piston"));
	Piston->SetupAttachment(DoorFrame);

	// Create door and attach it to Piston
	Door = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door"));
	Door->SetupAttachment(Piston);

	// Attach Object Circled to Door
	ObjectCircled->SetupAttachment(Piston);
}

void ASS_ImportantRoomsDoor_Base::BeginPlay()
{
	Super::BeginPlay();
}

void ASS_ImportantRoomsDoor_Base::OpenDoor(float Value)
{

}

