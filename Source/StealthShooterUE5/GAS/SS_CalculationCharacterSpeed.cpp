// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_CalculationCharacterSpeed.h"
#include "SS_AbilitySystemComponent.h"
#include "SS_CharacterAttributeSet.h"
#include "../Characters/SSCharacter_Base.h"


// Helper struct for fetching the stats necessery for the calculation
struct FSpeedStatics
{
	// Capchuredef declaration for attributes
	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentWalkSpeed);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentCrouchSpeed);

	// Default contructor
	FSpeedStatics()
	{
		// Capthuredef definition for attributes
		DEFINE_ATTRIBUTE_CAPTUREDEF(USS_CharacterAttributeSet, CurrentWalkSpeed, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USS_CharacterAttributeSet, CurrentCrouchSpeed, Source, false);
	}
};

// Static helper function to quickly fetch the speed capture attributes
static const FSpeedStatics& SpeedStatics()
{
	static FSpeedStatics SpeedStatic;
	return SpeedStatic;
}

// Add all the capthuredef definitions to the list of relevant attributes to capture
USS_CalculationCharacterSpeed::USS_CalculationCharacterSpeed()
{
	RelevantAttributesToCapture.Add(SpeedStatics().CurrentWalkSpeedDef);
	RelevantAttributesToCapture.Add(SpeedStatics().CurrentCrouchSpeedDef);
}

// Do the speed calculations and modify speed accordingly
void USS_CalculationCharacterSpeed::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	// Obtain reference to the source ASC
	UAbilitySystemComponent* SourceABC = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceABC ? SourceABC->GetAvatarActor() : nullptr;

	// Get the owning GA Spec so that you can use its variables and tags
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

	// Aggregator Evaluate Parameters used during the attribute capture
	FAggregatorEvaluateParameters EvaluateParametrs;
	EvaluateParametrs.SourceTags = SourceTags;

	// Capturing current walk speed 
	float CurrentWalkSpeed;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(SpeedStatics().CurrentWalkSpeedDef, EvaluateParametrs, CurrentWalkSpeed);

	// Capturing current crouch speed 
	float CurrentCrouchSpeed;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(SpeedStatics().CurrentWalkSpeedDef, EvaluateParametrs, CurrentCrouchSpeed);

	// Performing the actual speed calculation
	if (SourceABC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Character.Status.SpeedStimulator"))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString("WORKED!"));
	}
}
