// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Locomotion.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"

void UAbility_Locomotion::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}
