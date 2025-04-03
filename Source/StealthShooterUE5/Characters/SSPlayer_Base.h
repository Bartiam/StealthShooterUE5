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

protected: // Functions

	virtual void BeginPlay() override;


};
