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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// - Health Variables - //

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, MaxHealth);

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentHealth);

	// - Speed Variables - //

	UPROPERTY(ReplicatedUsing = OnRep_CurrentSpeed, EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentSpeed;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentSpeed);

	// - Noise Variables - //

	UPROPERTY(ReplicatedUsing = OnRep_CurrentNoise, EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentNoise;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentNoise);

	// - Health Rep functions - //

	UFUNCTION()
	virtual void OnRep_CurrentHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	// - Speed Rep Functions - //

	UFUNCTION()
	virtual void OnRep_CurrentSpeed(const FGameplayAttributeData& OldValue);


	// - Noise Rep Functions - //

	UFUNCTION()
	virtual void OnRep_CurrentNoise(const FGameplayAttributeData& OldValue);
};
