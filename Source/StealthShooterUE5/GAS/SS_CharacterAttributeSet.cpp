// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "../Characters/SSCharacter_Base.h"

#include "Net/UnrealNetwork.h"

USS_CharacterAttributeSet::USS_CharacterAttributeSet()
{}

void USS_CharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);

	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, CurrentSpeed, COND_None, REPNOTIFY_OnChanged);

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

	if (Data.EvaluatedData.Attribute == GetCurrentSpeedAttribute())
	{
		// Transfer to a character CurrentSpeed
		if (ASSCharacter_Base* OwnerCharacter = Cast<ASSCharacter_Base>(GetOwningActor()))
			OwnerCharacter->Server_UpdateCharacterSpeed(GetCurrentSpeed());
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

void USS_CharacterAttributeSet::OnRep_CurrentSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, CurrentSpeed, OldValue);
}

void USS_CharacterAttributeSet::OnRep_CurrentNoise(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, CurrentNoise, OldValue);
}
