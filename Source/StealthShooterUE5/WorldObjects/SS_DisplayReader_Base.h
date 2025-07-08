// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSInteractableObject_Base.h"

#include "SS_DisplayReader_Base.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCodeEntred, FName, ReciavedCode, AActor*, Interactor);



UCLASS()
class STEALTHSHOOTERUE5_API ASS_DisplayReader_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()

public: // Variables

	UPROPERTY(BlueprintAssignable)
	FOnCodeEntred OnCodeEntred;

	UPROPERTY()
	TObjectPtr<class ASS_Door_Base> CurrentDoor;

	UFUNCTION()
	virtual void PlayActionsWhenTryedDoorOpen();

public: // Functions

	ASS_DisplayReader_Base();

protected: // Variables

	UPROPERTY()
	FTimerHandle TimerToIncorrectKey;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> DisplayWidget_Component;

	TObjectPtr<class USS_CardReaderWidget_Base> DisplayWidget_Pointer;

protected: // Functions

	virtual void BeginPlay() override;

	virtual void InteractableRelease_Implementation(AActor* Interactor) override;

	void SetCurrentSpecificationsToReader();

};
