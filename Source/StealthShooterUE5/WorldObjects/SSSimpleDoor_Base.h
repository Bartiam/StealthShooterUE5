// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SS_Door_Base.h"

#include "SSSimpleDoor_Base.generated.h"


UCLASS()
class STEALTHSHOOTERUE5_API ASSSimpleDoor_Base : public ASS_Door_Base
{
	GENERATED_BODY()
	
public:	// Functions
	
	ASSSimpleDoor_Base();

protected: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<UCurveFloat> LockDoorCurve;

	// How many need to rotation door
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	float OpenDoorRotateAngle = 0.f;

	// How many need to rotation door
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	float LockDoorRotateAngle = 0.f;

protected: // Functions

	virtual void InteractableRelease_Implementation(AActor* Interactor) override;

	UFUNCTION()
	void OpenDoor(float Value) override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private: // Variables

	FTimerHandle TimerToOpenInventory;

	float CurrentDoorRotateAngle = 0.f;

	FTimeline TimelineToOpenDoor_Lock;
};
