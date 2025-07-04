﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CardReaderWidget_Base.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

#include "../WorldObjects/SS_Door_Base.h"



void USS_CardReaderWidget_Base::SetBrushColorToOpenDoor(const bool& bIsDoorLock)
{
	if (!bIsDoorLock)
	{
		TextBlock->SetColorAndOpacity(OpenDoorColor);
		TextBlock->SetText(INVTEXT("Открыто"));
	}
	else
	{
		TextBlock->SetColorAndOpacity(LockDoorColor);
		TextBlock->SetText(TextWhenDoorLocked);
	}
}

void USS_CardReaderWidget_Base::BindOnCodeEntred(FPickUpItemInfo ItemInfo, AActor* Interactor)
{}

void USS_CardReaderWidget_Base::CodeEntryActivated()
{}

void USS_CardReaderWidget_Base::CodeEntryDeactivated() 
{}

void USS_CardReaderWidget_Base::ShowMessageEntry()
{ 
	TextBlock->SetText(ErrorMessage);
	PlayAnimation(AppearReaderMessage);
}
