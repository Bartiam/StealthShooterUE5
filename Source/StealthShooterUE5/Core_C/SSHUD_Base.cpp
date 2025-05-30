// Fill out your copyright notice in the Description page of Project Settings.


#include "SSHUD_Base.h"
#include "../UserInterface/SS_UIDuringTheGame_Base.h"

USS_UIDuringTheGame_Base* ASSHUD_Base::GetUIDuringTheGame()
{ return UI_DuringTheGameWidget; }

UUserWidget* ASSHUD_Base::GetInventoryWidget()
{
	return nullptr;
}

void ASSHUD_Base::BeginPlay()
{
	Super::BeginPlay();

	UI_DuringTheGameWidget = CreateWidget<USS_UIDuringTheGame_Base>(GetWorld(), UI_DuringTheGame_Class);
	UI_DuringTheGameWidget->AddToViewport();
}