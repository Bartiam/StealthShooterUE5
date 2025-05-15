// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SS_Door_Base.h"

#include "SS_ImportantRoomsDoor_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_ImportantRoomsDoor_Base : public ASS_Door_Base
{
	GENERATED_BODY()
	
public:	// Functions
	
	ASS_ImportantRoomsDoor_Base();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Piston;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Door;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<UCurveFloat> CurveRotateLock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	FRotator StartRotationLock = FRotator();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	FRotator EndRotationLock = FRotator();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	FVector LocationToOpenDoor = FVector();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	FVector LocationToLockDoor = FVector();

protected: // Functions

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void InteractableRelease_Implementation(const AActor* Interactor) override;

private: // Variables

	FTimeline TimelineToRotateLock;

private: // Functions

	UFUNCTION()
	virtual void OpenDoor(float Value) override;

	UFUNCTION()
	void OpenLock(float Value);
};
