// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "../SSData/SSTypes.h"
#include "../Interfaces/CharacterInterface.h"

#include "SS_CalculationCharacterSpeed.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_CalculationCharacterSpeed : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public: // Functions

	USS_CalculationCharacterSpeed();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
