// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CharacterAttributeSet.h"

#include "Net/UnrealNetwork.h"

USS_CharacterAttributeSet::USS_CharacterAttributeSet()
{}

void USS_CharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USS_CharacterAttributeSet, Damage, COND_None, REPNOTIFY_Always);
}

void USS_CharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, Health, OldValue);
}

void USS_CharacterAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USS_CharacterAttributeSet, Health, OldValue);
}
