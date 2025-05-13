// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_InportantRoomsDoor_Base.h"
#include "SS_CardReader_Base.h"
#include "Components/ChildActorComponent.h"


// Sets default values
ASS_InportantRoomsDoor_Base::ASS_InportantRoomsDoor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Frame"));
	SetRootComponent(DoorFrame);

	CardReader = CreateDefaultSubobject<UChildActorComponent>(FName("Card Reader"));
	CardReader->SetupAttachment(RootComponent);
	CardReader->SetChildActorClass(ASS_CardReader_Base::StaticClass());
	
}

// Called when the game starts or when spawned
void ASS_InportantRoomsDoor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASS_InportantRoomsDoor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

