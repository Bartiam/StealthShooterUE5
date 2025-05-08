// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SSInteractableObject_Base.h"
#include "Components/TimelineComponent.h"

#include "SSSimpleDoor_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSSimpleDoor_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()
	
public:	// Functions
	
	ASSSimpleDoor_Base();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	bool bIsDoorLock = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	TObjectPtr<UCurveFloat> DoorCurve;

	// How many need to rotation door
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	float DoorRotateAngle = 60.f;

protected: // Functions

	virtual void Interactable_Implementation(const AActor* Interactor) override;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OpenDoor(float Value);

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private: // Variables

	bool bIsDoorClosed = true;

	FTimeline TimelineToOpenDoor;
};
