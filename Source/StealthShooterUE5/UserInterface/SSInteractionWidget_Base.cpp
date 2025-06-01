// Fill out your copyright notice in the Description page of Project Settings.


#include "SSInteractionWidget_Base.h"



void USSInteractionWidget_Base::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(AppearMarkObject);
}
