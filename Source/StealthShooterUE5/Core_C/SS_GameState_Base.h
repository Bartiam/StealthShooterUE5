// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SS_GameState_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_GameState_Base : public AGameStateBase
{
	GENERATED_BODY()
	
public: // Functions

	UFUNCTION(BlueprintCallable)
	void SpawnPickUpItemFromActor(const class USS_ItemObject* ItemObject, const AActor* SpawnerActor);
};
