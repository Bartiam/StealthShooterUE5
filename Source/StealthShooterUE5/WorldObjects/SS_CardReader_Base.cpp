// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CardReader_Base.h"

ASS_CardReader_Base::ASS_CardReader_Base()
{
	
}

void ASS_CardReader_Base::InteractableRelease_Implementation(const AActor* Interactor)
{

}

void ASS_CardReader_Base::BeginPlay()
{
	Super::BeginPlay();

	if (GetParentActor())
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, GetParentActor()->GetName());
}

