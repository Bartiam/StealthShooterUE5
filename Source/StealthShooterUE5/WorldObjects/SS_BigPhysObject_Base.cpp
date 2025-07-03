// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_BigPhysObject_Base.h"

ASS_BigPhysObject_Base::ASS_BigPhysObject_Base()
{
	// Setup base specifications for ObjectCircled
	ObjectCircled->SetSimulatePhysics(true);
}

void ASS_BigPhysObject_Base::InteractableRelease_Implementation(AActor* Interactor)
{
	if (Interactor)
	{

	}
}
