// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "../Characters/SSCharacter_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

USS_CharacterAttributeSet::USS_CharacterAttributeSet()
{}

void USS_CharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Clamp CurrentHealth
	if (Attribute == GetCurrentHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
}

void USS_CharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentWalkSpeedAttribute())
	{
		// Transfer to a character CurrentWalkSpeed
		if (ASSCharacter_Base* OwnerCharacter = ICharacterInterface::Execute_GetOwnerCharacter(GetOwningActor()))
		{
			OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCurrentWalkSpeed();
		}
	}

	if (Data.EvaluatedData.Attribute == GetCurrentCrouchSpeedAttribute())
	{
		// Transfer to a character CurrentCrouchSpeed
		if (ASSCharacter_Base* OwnerCharacter = ICharacterInterface::Execute_GetOwnerCharacter(GetOwningActor()))
		{
			OwnerCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched = GetCurrentCrouchSpeed();
		}
	}
}