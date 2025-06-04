// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CardReaderWidget_Base.h"
#include "Components/Border.h"
#include "../WorldObjects/SS_Door_Base.h"



void USS_CardReaderWidget_Base::NativeConstruct()
{
	Super::NativeConstruct();

	ChangeColorBackgroundBorder();
}



void USS_CardReaderWidget_Base::ChangeColorBackgroundBorder()
{
	if (OwnerActor->GetIsDoorLock())
	{
		BackgroundBorder->SetBrushColor(LockDoorColor);
		OwnerActor->DoorOpened.AddDynamic(this, &ThisClass::ChangeColorBackgroundBorder);
	}
	else
	{
		BackgroundBorder->SetBrushColor(OpenDoorColor);
		OwnerActor->DoorOpened.RemoveAll(this);
	}
}
