// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Interfaces/Interactable.h"
#include "Components/TimelineComponent.h"

#include "SSSimpleDoor_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSSimpleDoor_Base : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	// Functions
	
	ASSSimpleDoor_Base();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Door;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UBoxComponent> OverlapBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	bool bIsClosed = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	bool bIsLock = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	TObjectPtr<UCurveFloat> DoorCurve;

	// How many need to rotation door
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	float DoorRotateAngle = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	float ClosedDoorYaw = 0.f;

protected: // Functions

	virtual void Interactable_Implementation() override;

	UFUNCTION()
	void OpenDoor(float Value);

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private: // Variables

	FTimeline TimelineToOpenDoor;
};
