// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_InportantRoomsDoor_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_InportantRoomsDoor_Base : public AActor
{
	GENERATED_BODY()
	
public:	// Functions
	
	ASS_InportantRoomsDoor_Base();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Specifications")
	int32 testint = 0;

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<UStaticMeshComponent> Door;

protected: // Functions
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
