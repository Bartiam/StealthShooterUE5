// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "../SSData/SSTypes.h"
#include "../Interfaces/CharacterInterface.h"

#include "SSCharacter_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSCharacter_Base : public ACharacter, public IAbilitySystemInterface, public ICharacterInterface
{
	GENERATED_BODY()

public:
	ASSCharacter_Base();

private: // Variables

	TObjectPtr<class ASSPlayerController_Base> CurrentPlayerController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USS_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USS_CharacterAttributeSet> AttributeSet;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Specifications")
	FCharacterMovementSpeed CharacterMovementSpeed;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> HitActorTrace = nullptr;

public: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Specifications")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Specifications")
	TArray<TSubclassOf<class USSGameplayAbility_Base>> StartupAbilities;

public: // Functions

	FCharacterMovementSpeed GetCharacterMovementSpeed() const;

	// - Character Interface - //
	virtual ASSCharacter_Base* GetOwnerCharacter_Implementation() override;

	virtual class ASSPlayerController_Base* GetOwnerCharacterController_Implementation() override;
	// ----------------------- //

	virtual void InitializeAttributes();

	virtual void GiveAbilities();

	// - Ability System Interface - //
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ---------------------------- //
};
