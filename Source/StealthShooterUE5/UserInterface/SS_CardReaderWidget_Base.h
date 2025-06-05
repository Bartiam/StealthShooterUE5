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

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText TextWhenDoorLocked = FText();

private: // Variables

	FLinearColor OpenDoorColor = FLinearColor(0.f, 1.f, 0.f ,0.25f);

	FLinearColor LockDoorColor = FLinearColor(1.f, 0.f, 0.f, 0.25f);

public: // Functions

	UFUNCTION()
	void SetBrushColorToOpenDoor(const bool& bIsDoorLock);
};
