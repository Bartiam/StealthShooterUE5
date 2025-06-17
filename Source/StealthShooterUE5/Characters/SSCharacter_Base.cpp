// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCharacter_Base.h"

#include "../GAS/SS_AbilitySystemComponent.h"
#include "../GAS/Abilities/SSGameplayAbility_Base.h"
#include "../GAS/SS_CharacterAttributeSet.h"
#include "../Controllers/SSPlayerController_Base.h"
#include "../Controllers/SS_AIController_Base.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ASSCharacter_Base::ASSCharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ASC
	AbilitySystemComponent = CreateDefaultSubobject<USS_AbilitySystemComponent>(FName("Ability System Component"));

	// Create AS
	AttributeSet = CreateDefaultSubobject<USS_CharacterAttributeSet>(FName("Attribute Set"));

	// Base specifications for PlayerMovement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;

	// Set base rotation for mesh
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}



// Called when the game starts or when spawned
void ASSCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
}



FCharacterMovementSpeed ASSCharacter_Base::GetCharacterMovementSpeed() const
{ return CharacterMovementSpeed; }



ASSCharacter_Base* ASSCharacter_Base::GetOwnerCharacter_Implementation()
{ return this; }



ASSPlayerController_Base* ASSCharacter_Base::GetOwnerPlayerController_Implementation()
{ return CurrentPlayerController; }



ASS_AIController_Base* ASSCharacter_Base::GetOwnerAIController_Implementation()
{ return CurrentAIController; }



UAbilitySystemComponent* ASSCharacter_Base::GetAbilitySystemComponent() const
{ return AbilitySystemComponent; }



FGenericTeamId ASSCharacter_Base::GetGenericTeamId() const
{ return TeamId; }




void ASSCharacter_Base::InitializeAttributes()
{
	// Check ASC and Effect != nullptr
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		// Create effect context for gameplay effect 
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		// The source of the effect created
		EffectContext.AddSourceObject(this);
		// Create a specification for the effect
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		// Check valid
		if (SpecHandle.IsValid())
		{
			// Apply gameplay effect to self
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
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
}



void ASSCharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	SetOwner(NewController);



	if (IsValid(NewController))
	{
		if (ActorHasTag(FName("Player")))
			CurrentPlayerController = Cast<ASSPlayerController_Base>(NewController);
		else
			CurrentAIController = Cast<ASS_AIController_Base>(NewController);
	}



	InitializeAttributes();
	GiveAbilities();
}



UAISense_Sight::EVisibilityResult ASSCharacter_Base::CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation,
	int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength, int32* UserData,
	const FOnPendingVisibilityQueryProcessedDelegate* Delegate)
{
	FVector CapsuleLocation = GetCapsuleComponent()->GetComponentLocation();

	FVector UpperPartCapsule = FVector(CapsuleLocation.X, CapsuleLocation.Y, CapsuleLocation.Z + GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 20.f);
	FHitResult HitResult;

	bool HadBlockingHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Context.ObserverLocation,
		UpperPartCapsule,
		ECC_Visibility,
		FCollisionQueryParams(FName("Name_AILineOfSight"), false, Context.IgnoreActor)
	);

	if (!HadBlockingHit || (IsValid(HitResult.GetActor()) && HitResult.GetActor()->IsOwnedBy(this)))
	{
		OutSeenLocation = UpperPartCapsule;
		OutNumberOfLoSChecksPerformed = 1;
		OutNumberOfAsyncLosCheckRequested = 0;
		OutSightStrength = 1;
		return UAISense_Sight::EVisibilityResult::Visible;
	}

	OutNumberOfLoSChecksPerformed = 1;
	OutNumberOfAsyncLosCheckRequested = 0;
	OutSightStrength = 0;
	return UAISense_Sight::EVisibilityResult::NotVisible;
}