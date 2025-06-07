// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Card_Base.h"
#include "Components/TextRenderComponent.h"

ASS_Card_Base::ASS_Card_Base()
{
	ObjectCircled->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
	ObjectCircled->SetWorldScale3D(FVector(3.f));

	// Create and set base specification for Card Name
	CardName_InTheWorld = CreateDefaultSubobject<UTextRenderComponent>(FName("Card Name"));
	CardName_InTheWorld->SetupAttachment(ObjectCircled);
	CardName_InTheWorld->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	CardName_InTheWorld->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	CardName_InTheWorld->SetRelativeLocation(FVector(0.f, 0.1f, 0.f));
	CardName_InTheWorld->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	CardName_InTheWorld->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
	CardName_InTheWorld->TextRenderColor = FColor::Black;
	CardName_InTheWorld->WorldSize = 24.f;
}

