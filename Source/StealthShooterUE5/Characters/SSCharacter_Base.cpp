// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacter_Base.h"

#include "../GAS/SS_AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "../GAS/SS_CharacterAttributeSet.h"

// Sets default values
ASSCharacter_Base::ASSCharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ASC
	AbilitySystemComponent = CreateDefaultSubobject<USS_AbilitySystemComponent>(FName("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create AS
	AttributeSet = CreateDefaultSubobject<USS_CharacterAttributeSet>(FName("Attribute Set"));
	AttributeSet->OwnerMovementComponent = GetCharacterMovement();

	// Set character TPS
	NetUpdateFrequency = 30.f;
}

// Called when the game starts or when spawned
void ASSCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
}

void ASSCharacter_Base::InitializeAttributes()
{
	// Check ASC and Effect != nullptr
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		// Create effect context for gameplay effect 
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		// The source of the effect
		EffectContext.AddSourceObject(this);
		// Create a specification for the effect
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		// Check valid
		if (SpecHandle.IsValid())
		{
			// Apply gameplay effect to self
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ASSCharacter_Base::GiveAbilities()
{
	// Check that it is a server and ASC != nullptr
	if (HasAuthority() && AbilitySystemComponent)
	{
		// Gets all abilities
		for (TSubclassOf<UGameplayAbility> StartupAbility : CharacterAbilities)
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1));
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