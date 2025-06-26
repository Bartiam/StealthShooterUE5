// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ItemSpawner_Base.h"



ASS_ItemSpawner_Base::ASS_ItemSpawner_Base()
{
	PrimaryActorTick.bCanEverTick = false;

}



void ASS_ItemSpawner_Base::BeginPlay()
{
	Super::BeginPlay();
	
}



void ASS_ItemSpawner_Base::SpawnItemsSecurityRoom()
{


	SpawnObjectInTheRoom();
}



void ASS_ItemSpawner_Base::SpawnObjectInTheRoom()
{
	if (!CheckingSpawnedObjectInTheRoom()) return;

	switch (RoomType)
	{
	case ESSRoomType::BeginPlay_Room:
		break;
	case ESSRoomType::Security_Room:
		SpawnItemsSecurityRoom();
		break;
	case ESSRoomType::Laboratory_Room:
		break;
	case ESSRoomType::SectorHeld_Room:
		break;
	case ESSRoomType::Sector_Experiments:
		break;
	case ESSRoomType::Distributions_Room:
		break;
	case ESSRoomType::Arena_Room:
		break;
	}
}

bool ASS_ItemSpawner_Base::CheckingSpawnedObjectInTheRoom()
{
	return false;
}

