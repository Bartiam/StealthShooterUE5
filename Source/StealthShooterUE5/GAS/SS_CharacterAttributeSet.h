// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "SS_CharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class STEALTHSHOOTERUE5_API USS_CharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public: 

	USS_CharacterAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// - Health Variables - //

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, MaxHealth);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentHealth);

	// - Speed Variables - //

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentWalkSpeed;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentWalkSpeed);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentCrouchSpeed;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentCrouchSpeed);

	// - Noise Variables - //

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentNoise;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentNoise);
};
