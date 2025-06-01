// Fill out your copyright notice in the Description page of Project Settings.


#include "SSHUD_Base.h"
#include "../UserInterface/SS_DuringTheGame_Base.h"
#include "Blueprint/UserWidget.h"



USS_DuringTheGame_Base* ASSHUD_Base::GetUIDuringTheGame()
{ return UI_DuringTheGameWidget; }



UUserWidget* ASSHUD_Base::GetInventoryWidget()
{ return InventoryWidget; }



void ASSHUD_Base::BeginPlay()
{
	Super::BeginPlay();

	// Create UI during the game
	UI_DuringTheGameWidget = CreateWidget<USS_DuringTheGame_Base>(GetWorld(), UI_DuringTheGame_Class);
	UI_DuringTheGameWidget->AddToViewport();

	// Create Inventory widget
	InventoryWidget = CreateWidget<UUserWidget>(GetWorld(), Inventory_Class);
}