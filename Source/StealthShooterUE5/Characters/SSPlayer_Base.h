// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacter_Base.h"

#include "../SSData/SSTypes.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Montages")
	FCharacterMontages PlayerMontages;

protected: // Functions

	virtual void BeginPlay() override;

private: // Functions 

	UFUNCTION()
	void CheckJacketOnTheCharacter();

public: // Variables

	UPROPERTY(BlueprintReadOnly)
	FVector2D CurrentDirection = FVector2D::Zero();

public: // Multiplay functions

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void Server_PlayDodgeMontages();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	virtual void NetMulticast_PlayDodgeMontages();
};
