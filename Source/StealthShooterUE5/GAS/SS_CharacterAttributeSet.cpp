// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "../Characters/SSCharacter_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Net/UnrealNetwork.h"

USS_CharacterAttributeSet::USS_CharacterAttributeSet()
{}

void USS_CharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);

	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, CurrentWalkSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, CurrentCrouchSpeed, COND_None, REPNOTIFY_OnChanged);

	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, CurrentNoise, COND_None, REPNOTIFY_OnChanged);
}

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
		if (ASSCharacter_Base* OwnerCharacter = Cast<ASSCharacter_Base>(GetOwningActor()))
		{
			OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCurrentWalkSpeed();
		}
	}

	if (Data.EvaluatedData.Attribute == GetCurrentCrouchSpeedAttribute())
	{
		// Transfer to a character CurrentCrouchSpeed
		if (ASSCharacter_Base* OwnerCharacter = Cast<ASSCharacter_Base>(GetOwningActor()))
		{
			OwnerCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched = GetCurrentCrouchSpeed();
		}
	}
}

void USS_CharacterAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, CurrentHealth, OldValue);
}

void USS_CharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, MaxHealth, OldValue);
}

void USS_CharacterAttributeSet::OnRep_CurrentWalkSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, CurrentWalkSpeed, OldValue);

	// Transfer to a character CurrentWalkSpeed
	if (ASSCharacter_Base* OwnerCharacter = Cast<ASSCharacter_Base>(GetOwningActor()))
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCurrentWalkSpeed();
	}
}

void USS_CharacterAttributeSet::OnRep_CurrentCrouchSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, CurrentCrouchSpeed, OldValue);

	// Transfer to a character CurrentCrouchSpeed
	if (ASSCharacter_Base* OwnerCharacter = Cast<ASSCharacter_Base>(GetOwningActor()))
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched = GetCurrentCrouchSpeed();
	}
}

void USS_CharacterAttributeSet::OnRep_CurrentNoise(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, CurrentNoise, OldValue);
}
