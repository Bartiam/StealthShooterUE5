// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_InportantRoomsDoor_Base.h"



// Sets default values
ASS_InportantRoomsDoor_Base::ASS_InportantRoomsDoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create door frame and setup it as a root component
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Frame"));
	SetRootComponent(DoorFrame);
	// Create piston and setup it to door frame
	Piston = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piston"));
	Piston->SetupAttachment(DoorFrame);
	// Create door and setup it to Piston
	Door = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door"));
	Door->SetupAttachment(Piston);
	// Create forward lock and setup it to door
	Lock = CreateDefaultSubobject<UStaticMeshComponent>(FName("Lock"));
	Lock->SetupAttachment(Door);
}

void ASS_InportantRoomsDoor_Base::OpenDoor(float Value)
{

}

