// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../SSData/SSTypes.h"

#include "SSWorldGeneration_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASSWorldGeneration_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSWorldGeneration_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
