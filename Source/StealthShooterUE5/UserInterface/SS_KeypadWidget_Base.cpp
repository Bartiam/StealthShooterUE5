// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_KeypadWidget_Base.h"
#include "../WorldObjects/SS_DisplayReader_Base.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/VerticalBox.h"



void USS_KeypadWidget_Base::CallOnCodeEntred(FName EntredCode, AActor* Interactor)
{
	OwnerCodeReader->OnCodeEntred.Broadcast(EntredCode, Interactor);
}



void USS_KeypadWidget_Base::CodeEntryActivated()
{
	SizeBoxToTextBlock->SetVisibility(ESlateVisibility::Hidden);
	SizeBoxToEnterTextBox->SetVisibility(ESlateVisibility::Visible);
	ButtonVerticalBox->SetVisibility(ESlateVisibility::Visible);
}



void USS_KeypadWidget_Base::CodeEntryDeactivated()
{
	SizeBoxToTextBlock->SetVisibility(ESlateVisibility::Visible);
	SizeBoxToEnterTextBox->SetVisibility(ESlateVisibility::Hidden);
	ButtonVerticalBox->SetVisibility(ESlateVisibility::Hidden);
	EnterTextBox->SetText(FText());
}