// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSInteractableObject_Base.h"
#include "Components/TimelineComponent.h"
#include "../WorldObjects/SS_ItemObject.h"

#include "SS_Door_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_Door_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()
	
public: // Functions

	ASS_Door_Base();

	bool GetIsDoorLock() const;

	virtual void SetIsDoorLock(const bool& NewValue);

	void OpenAndBindToPlayerInventory(AActor* Interactor);

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	bool bIsDoorLock = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	FKeyPermission DoorKeyPermission = FKeyPermission();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<UCurveFloat> OpenDoorCurve;

	bool bIsDoorClosed = true;

	FTimeline TimelineToOpenDoor;

	// Texts for UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Specifications")
	FText TextWhenDoorIsLocked = FText();

protected: // Functions

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OpenDoor(float Value);

	void BindCurveToTimeline(UCurveFloat* CurrentCurve, FTimeline& CurrentTimeline);

	UFUNCTION()
	void BindOnGetKeyToOpenDoor(FPickUpItemInfo ItemInfo, AActor* Interactor);

private: // Variables

	FText TextWhenSelectedIncorrectKey = INVTEXT("Это не подойдёт!");
};



