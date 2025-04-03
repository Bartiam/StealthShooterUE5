// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Walk.h"

#include "GameplayTagContainer.h"

UAbility_Walk::UAbility_Walk()
{
	// Add Input GameplayTag for GameplayAbility
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Input.Walk")));

	// Add Status GameplayTag for Owner Character
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Status.Walk")));
}

void UAbility_Walk::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, FString(TEXT("It's WORK!!!")));
}
