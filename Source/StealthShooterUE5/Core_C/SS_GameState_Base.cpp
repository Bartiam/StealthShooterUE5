// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_GameState_Base.h"
#include "../WorldObjects/SS_PickUpItem_Base.h"
#include "Kismet/KismetSystemLibrary.h"



void ASS_GameState_Base::SpawnPickUpItemFromActor(const USS_ItemObject* ItemObject, const AActor* SpawnerActor)
{
	FVector ActorLocation = SpawnerActor->GetActorLocation();
	FVector ActorForwardVector = SpawnerActor->GetActorForwardVector();

	FVector SpawnLocation = ActorLocation + (ActorForwardVector * 150.f);

	GetWorld()->SpawnActor<ASS_PickUpItem_Base>(ItemObject->ItemInfo.ItemClass, FTransform(SpawnLocation));
}
