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
	// Sets default values for this actor's properties
	ASS_RoomGeneration_Base();

protected: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Room Specifications")
	TArray<TObjectPtr<class ASS_RoomMarker_Base>> NPCMarkers;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
