// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SS_CardReaderWidget_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_CardReaderWidget_Base : public UUserWidget
{
	GENERATED_BODY()
	
protected: // Variables

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class UBorder> BackgroundBorder;

public: // Variables

	virtual void NativeConstruct() override;

	TObjectPtr<class ASS_Door_Base> OwnerActor;

private: // Variables

	FLinearColor LockDoorColor = FLinearColor(1.f, 0.f, 0.f, 0.25f);

	FLinearColor OpenDoorColor = FLinearColor(0.f, 1.f, 0.f ,0.25f);

private: // Functions

	UFUNCTION()
	void ChangeColorBackgroundBorder();
};
