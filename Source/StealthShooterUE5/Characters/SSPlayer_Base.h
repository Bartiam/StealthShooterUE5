// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacter_Base.h"

#include "../Interfaces/Interactable.h"

#include "SSPlayer_Base.generated.h"


UCLASS()
class STEALTHSHOOTERUE5_API ASSPlayer_Base : public ASSCharacter_Base
{
	GENERATED_BODY()
	
public:
	ASSPlayer_Base();

protected: // Variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> HolsterComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> Jacket;

	UPROPERTY(BlueprintReadOnly)
	AActor* HitActorTrace = nullptr;
	
protected: // Functions

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

private: // Variables

	TObjectPtr<class ASSPlayerController_Base> CurrentPlayerController;

	FTimerHandle TimerToSearching;

	// - Variables for trace - //
	TArray<AActor*> IgnoreActors;
	float SphereTraceLength = 300.f;
	float SphereTraceRadius = 5.f;

private: // Functions 

	UFUNCTION()
	void CheckJacketOnTheCharacter();

	UFUNCTION()
	void SearchingObjectsLinetrace();

public: // Functions

	virtual ASSPlayer_Base* GetOwnerPlayer_Implementation() override;

	virtual class ASSPlayerController_Base* GetOwnerPlayerController_Implementation() override;
};
