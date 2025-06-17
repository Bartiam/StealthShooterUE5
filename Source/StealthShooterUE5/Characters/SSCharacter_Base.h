// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameplayEffectTypes.h"
#include "../SSData/SSTypes.h"

#include "../Interfaces/CharacterInterface.h"
#include "Perception/AISightTargetInterface.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"

#include "SSCharacter_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSCharacter_Base : public ACharacter, public IAbilitySystemInterface,
	public ICharacterInterface, public IAISightTargetInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ASSCharacter_Base();

private: // Variables

	TObjectPtr<class ASSPlayerController_Base> CurrentPlayerController;

	TObjectPtr<class ASS_AIController_Base> CurrentAIController;

protected: // Variables

	FGenericTeamId TeamId = FGenericTeamId();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USS_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USS_CharacterAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Specifications")
	FCharacterMovementSpeed CharacterMovementSpeed;

	UPROPERTY(BlueprintReadOnly)
	AActor* HitActorTrace;

protected: // Functions

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

public: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Specifications")
	int32 ID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Specifications")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Specifications")
	TArray<TSubclassOf<class USSGameplayAbility_Base>> StartupAbilities;

public: // Functions

	FCharacterMovementSpeed GetCharacterMovementSpeed() const;

	// - Character Interface - //
	virtual ASSCharacter_Base* GetOwnerCharacter_Implementation() override;

	virtual class ASSPlayerController_Base* GetOwnerPlayerController_Implementation() override;

	virtual class ASS_AIController_Base* GetOwnerAIController_Implementation() override;
	// ----------------------- //

	virtual void InitializeAttributes();

	virtual void GiveAbilities();

	// - Ability System Interface - //
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ---------------------------- //

	// - Sense Sight Interface - //
	virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation,
		int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength,
		int32* UserData = nullptr, const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr) override;
	// ---------------------------- //

	// - Team Agent Interface - //
	virtual FGenericTeamId GetGenericTeamId() const override;
	// ---------------------------- //
};
