// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacter_Base.h"

#include "../GAS/SS_AbilitySystemComponent.h"
#include "../GAS/Abilities/SSGameplayAbility_Base.h"
#include "../GAS/SS_CharacterAttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"


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

	// Set character TPS
	NetUpdateFrequency = 30.f;

	// Base specifications for PlayerMovement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->SetIsReplicated(true);
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
		for (TSubclassOf<USSGameplayAbility_Base> StartupAbility : StartupAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbility, 1, 
				static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID));

			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}

	Crouch();
}

UAbilitySystemComponent* ASSCharacter_Base::GetAbilitySystemComponent() const
{ return AbilitySystemComponent; }

ASSCharacter_Base* ASSCharacter_Base::GetCharacter_Implementation()
{ return this; }

void ASSCharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void ASSCharacter_Base::Client_UpdateCharacterSpeed_Implementation(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void ASSCharacter_Base::Server_UpdateCharacterSpeed_Implementation(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	Client_UpdateCharacterSpeed(NewSpeed);
}