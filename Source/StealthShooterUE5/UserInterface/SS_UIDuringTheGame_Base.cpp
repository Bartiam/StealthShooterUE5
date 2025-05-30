// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_UIDuringTheGame_Base.h"
#include "../GAS/SS_CharacterAttributeSet.h"

void USS_UIDuringTheGame_Base::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetOwningPlayerPawn()->Implements<UCharacterInterface>())
		OwningCharacter = ICharacterInterface::Execute_GetOwnerCharacter(GetOwningPlayerPawn());
}