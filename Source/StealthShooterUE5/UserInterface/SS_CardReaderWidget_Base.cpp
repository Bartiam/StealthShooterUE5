// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CardReaderWidget_Base.h"
#include "Components/Border.h"
#include "../WorldObjects/SS_Door_Base.h"
#include "../WorldObjects/SS_DisplayReader_Base.h"



void USS_CardReaderWidget_Base::SetBrushColorToOpenDoor(const bool& bIsDoorLock)
{
	if (!bIsDoorLock)
		BackgroundBorder->SetBrushColor(OpenDoorColor);
	else
		BackgroundBorder->SetBrushColor(LockDoorColor);
}
