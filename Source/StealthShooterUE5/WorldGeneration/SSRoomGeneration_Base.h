// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SSRoomDataAsset_Base.h"

#include "SSRoomGeneration_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSRoomGeneration_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSRoomGeneration_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room Configuration")
	TObjectPtr<USSRoomDataAsset_Base> RoomConfig;

};
