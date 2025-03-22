// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../../DataLibraries/DataTypes.h"

#include "SS_GameplayAbility_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_GameplayAbility_Base : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	USS_GameplayAbility_Base();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESSAbilityInputID AbilityInputID;
};
