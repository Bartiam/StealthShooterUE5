// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSInteractableObject_Base.h"
#include "Components/TimelineComponent.h"

#include "SS_Door_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_Door_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()
	
public: // Functions

	ASS_Door_Base();

	bool GetIsDoorLock() const;

	void SetIsDoorLock(const bool& NewValue);

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	bool bIsDoorLock = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<UCurveFloat> OpenDoorCurve;

	bool bIsDoorClosed = true;

	FTimeline TimelineToOpenDoor;

protected: // Functions

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OpenDoor(float Value);

	void BindCurveToTimeline(UCurveFloat* CurrentCurve, FTimeline& CurrentTimeline);
};
