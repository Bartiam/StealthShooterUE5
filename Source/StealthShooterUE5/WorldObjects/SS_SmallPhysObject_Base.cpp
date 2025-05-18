// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_SmallPhysObject_Base.h"

ASS_SmallPhysObject_Base::ASS_SmallPhysObject_Base()
{
	ObjectCircled->SetSimulatePhysics(true);
	ObjectCircled->SetCollisionProfileName("PhysicsActor");
}

void ASS_SmallPhysObject_Base::InteractableRelease_Implementation(const AActor* Interactor)
{
	
}

void ASS_SmallPhysObject_Base::InteractableHeld_Implementation(const AActor* Interactor)
{
	
}