// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Card_Base.h"

ASS_Card_Base::ASS_Card_Base()
{
	ObjectCircled->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
	ObjectCircled->SetWorldScale3D(FVector(3.f));
}
