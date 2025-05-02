// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSGameplayAbility_Base.h"

#include "../../Interfaces/CharacterInterface.h"

#include "SSInteractAbility_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USSInteractAbility_Base : public USSGameplayAbility_Base
{
	GENERATED_BODY()
	
protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact specifications")
	float LineTraceLength = 0.f;

	TArray<AActor*> IgnoreActors;

protected: // Functions

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
};
