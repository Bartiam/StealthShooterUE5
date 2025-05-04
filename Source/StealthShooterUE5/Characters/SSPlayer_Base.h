// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacter_Base.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Line Trace Length")
	float LineTraceLength = 0.f;
	
protected: // Functions

	virtual void BeginPlay() override;

private: // Variables

	TArray<AActor*> IgnoreActors;

	FTimerHandle TimerToSearchObjects;

private: // Functions 

	UFUNCTION()
	void CheckJacketOnTheCharacter();

	UFUNCTION()
	void LineTraceSearchInteractionObjects();

public: // Functions

	virtual class UCameraComponent* GetPlayerCameraComponent_Implementation() const override;
};
