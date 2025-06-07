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
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;

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

	if (!IsValid(SourceASC) && !IsValid(SourceActor)) return;

	// Performing the actual speed calculation
	if (SourceActor->Implements<UCharacterInterface>())
	{
		FCharacterMovementSpeed CharacterMovementSpeed = ICharacterInterface::Execute_GetOwnerCharacter(SourceActor)->GetCharacterMovementSpeed();
		float NewWalkSpeed = 0.f;
		float NewCrouchedSpeed = 0.f;

		// Setting base character speed
		if (SourceASC->HasMatchingGameplayTag(CharacterMovementSpeed.CrouchTag) &&
			SourceASC->HasMatchingGameplayTag(CharacterMovementSpeed.WalkTag))
		{
			NewCrouchedSpeed = CharacterMovementSpeed.CrouchedWalkSpeed;
		}
		else if (SourceASC->HasMatchingGameplayTag(CharacterMovementSpeed.CrouchTag))
		{
			NewCrouchedSpeed = CharacterMovementSpeed.CrouchSpeed;
		}
		else if (SourceASC->HasMatchingGameplayTag(CharacterMovementSpeed.WalkTag))
		{
			NewWalkSpeed = CharacterMovementSpeed.WalkSpeed;
		}
		else
		{
			NewWalkSpeed = CharacterMovementSpeed.RunSpeed;
		}

		// Update character speed from baff/debaff
		if (SourceASC->HasMatchingGameplayTag(FGameplayTag(CharacterMovementSpeed.SpeedStimulatoTag)))
		{
			NewWalkSpeed *= CharacterMovementSpeed.ImproveSpeedFromStimulator;
			NewCrouchedSpeed *= CharacterMovementSpeed.ImproveSpeedFromStimulator;
		}

		// Apply new speed
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(SpeedStatics().CurrentWalkSpeedProperty, EGameplayModOp::Override, NewWalkSpeed));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(SpeedStatics().CurrentCrouchSpeedProperty, EGameplayModOp::Override, NewCrouchedSpeed));
	}
}
