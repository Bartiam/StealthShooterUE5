// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSLamp_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSLamp_Base : public AActor
{
	GENERATED_BODY()
	
public: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsLampBlink = false;

public:	// functions
	// Sets default values for this actor's properties
	ASSLamp_Base();



	


protected: // Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
