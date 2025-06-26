// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSSimpleDoor_Base.h"
#include "SS_Chest_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_Chest_Base : public ASSSimpleDoor_Base
{
	GENERATED_BODY()
	
protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TObjectPtr<class UBoxComponent>> SpawnPlaces;
};
