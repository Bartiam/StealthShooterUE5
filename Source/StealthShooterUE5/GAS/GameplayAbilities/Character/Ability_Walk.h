// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "Ability_Walk.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API UAbility_Walk : public UGameplayAbility
{
	GENERATED_BODY()


protected: // Functions

	UAbility_Walk();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
