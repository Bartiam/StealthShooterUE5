// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_DuringTheGame_Base.h"
#include "Components/TextBlock.h"



void USS_DuringTheGame_Base::SetNewTextToTextBlock(const FText NewText)
{
	ScreenMessage->SetText(NewText);
	PlayAnimation(AppearScreenMessage);
}
