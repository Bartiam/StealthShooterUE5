// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Interfaces/Interactable.h"

#include "SSSimpleDoor_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSSimpleDoor_Base : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSSimpleDoor_Base();

protected: // Functions

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interactable_Implementation() override;

	UFUNCTION(Server, Reliable)
	void Server_OpenDoor();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Door;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Platband;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UBoxComponent> OverlapBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	bool bIsClosed = false;


	// How many need to rotation door
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	float OpenDoorYaw = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Specifications")
	float ClosedDoorYaw = 0.f;

private: // Variables

	FTimerHandle TimerToOpenDoor;

private: // Functions
	
	UFUNCTION(NetMulticast, Reliable)
	void ChangeRotationDoor();
};
