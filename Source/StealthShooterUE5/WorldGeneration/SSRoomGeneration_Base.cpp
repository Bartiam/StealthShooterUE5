// Fill out your copyright notice in the Description page of Project Settings.


#include "SSRoomGeneration_Base.h"

// Sets default values
ASSRoomGeneration_Base::ASSRoomGeneration_Base()
{

}

// Called when the game starts or when spawned
void ASSRoomGeneration_Base::BeginPlay()
{
	Super::BeginPlay();
	
	switch (RoomConfig->RoomType)
	{
	case ESSRoomTypes::Begin_Play_Room:
		break;
	case ESSRoomTypes::End_Play_Room:
		break;
	case ESSRoomTypes::Laboratory_Room:
		break;
	case ESSRoomTypes::Security_Room:
		break;
	case ESSRoomTypes::Distribution_Room:
		break;
	case ESSRoomTypes::Experimental_Room:
		break;
	case ESSRoomTypes::Arena_Room:
		break;
	case ESSRoomTypes::Surveillance_Room:
		break;
	}
}