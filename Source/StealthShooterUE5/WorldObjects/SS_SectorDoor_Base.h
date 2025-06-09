// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SS_Door_Base.h"
#include "SS_SectorDoor_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_SectorDoor_Base : public ASS_Door_Base
{
	GENERATED_BODY()
	
public: // Functions

	ASS_SectorDoor_Base();

	virtual void InteractableRelease_Implementation(AActor* Interactor) override;

	virtual void TryToOpenDoor(FPickUpItemInfo ItemInfo, AActor* Interactor) override;
	
protected: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	FVector LocationToOpenDoor = FVector();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	FVector LocationToLockDoor = FVector();

private: // Functions

	UFUNCTION()
	virtual void OpenDoor(float Value) override;

	virtual void BeginPlay() override;
};
