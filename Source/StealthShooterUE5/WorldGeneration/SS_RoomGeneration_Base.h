// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_RoomGeneration_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASS_RoomGeneration_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASS_RoomGeneration_Base();

protected:

	virtual void BeginPlay() override;

};
