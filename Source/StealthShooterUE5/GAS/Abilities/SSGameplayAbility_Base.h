// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "../../SSData/SSTypes.h"

#include "SSGameplayAbility_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USSGameplayAbility_Base : public UGameplayAbility
{
	GENERATED_BODY()

public: // Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input ID")
	ESSInputID AbilityInputID;
};
