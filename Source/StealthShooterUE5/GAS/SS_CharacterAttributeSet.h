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

	UPROPERTY()
	TObjectPtr<class UCharacterMovementComponent> OwnerMovementComponent; // Get from character

	USS_CharacterAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// - Variables - //

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentSpeed;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentSpeed);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData Noise;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, Noise);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, BaseHealth);

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, CurrentHealth);

	UPROPERTY(ReplicatedUsing = OnRep_Damage, EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(USS_CharacterAttributeSet, Damage);

	// - Rep functions - //

	UFUNCTION()
	virtual void OnRep_CurrentHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);
};
