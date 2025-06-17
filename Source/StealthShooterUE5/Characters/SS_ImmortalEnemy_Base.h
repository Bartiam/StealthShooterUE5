// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacter_Base.h"
#include "Perception/AISightTargetInterface.h"

#include "SS_ImmortalEnemy_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_ImmortalEnemy_Base : public ASSCharacter_Base, public IAISightTargetInterface
{
	GENERATED_BODY()

public: // Functions

	ASS_ImmortalEnemy_Base();

	class UNavigationInvokerComponent* GetNavigationInvoker();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UNavigationInvokerComponent> NavigationInvoker;

protected: // Functions

	virtual void BeginPlay() override;
	
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation,
		int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength,
		int32* UserData = nullptr, const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr) override;
};
