// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USS_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USS_CharacterAttributeSet> AttributeSet;

	UFUNCTION()
	virtual void PossessedBy(AController* NewController) override;

public: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;

public: // Functions

	virtual void InitializeAttributes();

	virtual void GiveAbilities();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public: // Functions

	UFUNCTION(Client, Reliable)
	void Client_UpdateCharacterSpeed(float NewSpeed);

	UFUNCTION(Server, Reliable)
	void Server_UpdateCharacterSpeed(float NewSpeed);
};
