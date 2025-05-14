// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../SSData/SSTypes.h"
#include "SS_Door_Base.h"

#include "SS_ImportantRoomsDoor_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_ImportantRoomsDoor_Base : public ASS_Door_Base
{
	GENERATED_BODY()
	
public:	// Functions
	
	ASS_ImportantRoomsDoor_Base();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Piston;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Door;

protected: // Functions

	virtual void BeginPlay() override;

private: // Functions

	virtual void OpenDoor(float Value) override;
};
