// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacter_Base.h"

#include "../GAS/SS_AbilitySystemComponent.h"
#include "../GAS/GameplayAbilities/SS_GameplayAbility_Base.h"
#include "../GAS/SS_CharacterAttributeSet.h"

// Sets default values
ASSCharacter_Base::ASSCharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ASC
	AbilitySystemComponent = CreateDefaultSubobject<USS_AbilitySystemComponent>(FName("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// Create AS
	AttributeSet = CreateDefaultSubobject<USS_CharacterAttributeSet>(FName("Attribute Set"));
}

// Called when the game starts or when spawned
void ASSCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeAttributes();
	GiveAbilities();
}

void ASSCharacter_Base::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ASSCharacter_Base::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<USS_GameplayAbility_Base> StartupAbility : CharacterAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}
}

UAbilitySystemComponent* ASSCharacter_Base::GetAbilitySystemComponent() const
{ return AbilitySystemComponent; }

void ASSCharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void ASSCharacter_Base::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();

	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			FString(TEXT("Confirm")),
			FString(TEXT("Cancel")),
			FString(TEXT("ESSAbilityInputID")),
			static_cast<int32>(ESSAbilityInputID::Confirm),
			static_cast<int32>(ESSAbilityInputID::Cancel));

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

// Called to bind functionality to input
void ASSCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (GetAbilitySystemComponent() && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			FString(TEXT("Confirm")),
			FString(TEXT("Cancel")),
			FString(TEXT("ESSAbilityInputID")),
			static_cast<int32>(ESSAbilityInputID::Confirm),
			static_cast<int32>(ESSAbilityInputID::Cancel));

		GetAbilitySystemComponent()->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

