// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../SSData/SSTypes.h"

#include "SS_SpawnMarker_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASS_SpawnMarker_Base : public AActor
{
	GENERATED_BODY()
	
public:	

	ASS_SpawnMarker_Base();

protected: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESSSpawnMarker_Type MarkerType;

protected: // Functions

	virtual void BeginPlay() override;

};
