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
	
public: // Functions

	ASSPlayer_Base();

	virtual USS_InventoryComponent* GetPlayerInventory_Implementation() override;

protected: // Variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> HolsterComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> Jacket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USS_InventoryComponent> InventoryComponent;
	
protected: // Functions

	virtual void BeginPlay() override;

private: // Variables

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
};
