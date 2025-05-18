// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_PhysObject_Base.h"

ASS_PhysObject_Base::ASS_PhysObject_Base()
{
	ObjectCircled->SetSimulatePhysics(true);
	ObjectCircled->SetCollisionProfileName("PhysicsActor");
}

void ASS_PhysObject_Base::InteractableRelease_Implementation(const AActor* Interactor)
{
	
}

void ASS_PhysObject_Base::InteractableHeld_Implementation(const AActor* Interactor)
{
	
}