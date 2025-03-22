// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"

#include "../DataLibraries/DataTypes.h"

#include "SSCharacter_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSCharacter_Base : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASSCharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	class USS_AbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	class USS_CharacterAttributeSet* AttributeSet = nullptr;

	UFUNCTION()
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TArray<TSubclassOf<class USS_GameplayAbility_Base>> CharacterAbilities;

	virtual void InitializeAttributes();

	virtual void GiveAbilities();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
