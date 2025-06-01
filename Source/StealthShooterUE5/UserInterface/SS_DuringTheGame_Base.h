// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SS_DuringTheGame_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_DuringTheGame_Base : public UUserWidget
{
	GENERATED_BODY()

protected: // Variables

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ScreenMessage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> AppearScreenMessage;

public: // Functions

	void SetNewTextToTextBlock(const FText NewText);
};
